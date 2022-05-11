#ifndef ADDITIONAL_UTILITIES
#define ADDITIONAL_UTILITIES
#include <exception>
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

#include "json.hpp"
using json = nlohmann::json;

// klasa wyjątku używanego w programie
class GameException: public std::exception
{
    std::string text;
public:
    GameException(std::string s):text(s){}
    const char* what() const noexcept { return text.c_str(); }
};

// element na ekranie gry który można narysować
class GameElement: public sf::Drawable
{
protected:
    sf::Sprite sprite;
public:
    GameElement(sf::Texture &t, sf::Vector2f pos);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::FloatRect getGlobalBounds();
    bool onScreen(bool ignore_top = false);
};

// oblicza przesunięcie o jakie należy się przesunąć z danego miejsca w zależności od odległości i czasu klatki.
sf::Vector2f getNewPosition(sf::Vector2f &position, sf::Vector2f &destination, float elapsed_time);

// pobiera wartość z zmiennej json albo rzuca wyjątek
json getValueFromJson(json &data, std::string key, std::string &filename);
sf::Texture& getTextureByFilename(
    std::string texture_filename,
    std::unordered_map<std::string, sf::Texture> &t,
    std::string &filename
);

sf::Vector2f getDirection(json d, std::string &filename);

#endif
