#include "additionalUtilities.h"
#include <cmath>

#include "constants.h"

GameElement::GameElement(sf::Texture &t, sf::Vector2f pos)
{
    sprite.setTexture(t);
    sf::FloatRect sprite_size = sprite.getLocalBounds();
    sprite.setOrigin(sprite_size.width/2.0, sprite_size.height/2.0);
    sprite.setPosition(pos);
}

void GameElement::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

sf::FloatRect GameElement::getGlobalBounds()
{
    return sprite.getGlobalBounds();
}

bool GameElement::onScreen(bool ignore_top)
{
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.left > -rect.width && rect.left < GAME_WIDTH &&
           (ignore_top || rect.top > -rect.height) && rect.top < SCREEN_HEIGHT;
}

sf::Vector2f getNewPosition(sf::Vector2f &position, sf::Vector2f &destination, float elapsed_time)
{
    float x_diff = destination.x - position.x;
    float y_diff = destination.y - position.y;
    float move_distance = sqrt(pow(x_diff, 2) + pow(y_diff, 2));
    sf::Vector2f normalized(x_diff/move_distance, y_diff/move_distance);
    if(move_distance > ENEMY_SPEED * elapsed_time)
        move_distance = ENEMY_SPEED * elapsed_time;
    else
        return sf::Vector2f(destination.x, destination.y);
    return sf::Vector2f(
        position.x + move_distance * normalized.x,
        position.y + move_distance * normalized.y
    );
}

json getValueFromJson(json &data, std::string key, std::string &filename)
{
    if(!data.contains(key))
        throw GameException("Missing value \""+key+"\" in file: "+filename);
    return data[key];
}

sf::Texture& getTextureByFilename(
    std::string texture_filename,
    std::unordered_map<std::string, sf::Texture> &t,
    std::string &filename
) {
    try
    {
        return t.at(texture_filename);
    }
    catch(std::out_of_range &e)
    {
        throw GameException("Missing texture filename in file "+filename);
    }
}

sf::Vector2f getDirection(json d, std::string &filename)
{
    if(!d.is_array() || d.size() < 2)
        throw GameException("wrong direction values in file "+filename);
    return sf::Vector2f(d[0], d[1]);
}
