#include "player.h"
#include "constants.h"

Player::Player(sf::Texture &t, sf::Texture &it, std::vector<BulletType> bt, float cooldown):
    GameElement(t, sf::Vector2f(GAME_WIDTH/2, SCREEN_HEIGHT - 50)),
    ShootAction(bt, cooldown), immortal_time(0),
    normal_texture(t), immortal_texture(it),
    health(START_HEALTH), damage(1),
    set_texture_normal(false)
{}

void Player::update(sf::Vector2i mouse_position, std::vector<std::shared_ptr<Bullet>> &bullets, float elapsed_time)
{
    move(mouse_position);
    shoot(bullets, elapsed_time);
    if(immortal_time > 0)
        immortal_time -= elapsed_time;
    else if(set_texture_normal)
    {
        set_texture_normal = false;
        sprite.setTexture(normal_texture);
    }
}

void Player::move(sf::Vector2i mouse_position)
{
    if(mouse_position.x > 0 && mouse_position.x < GAME_WIDTH &&
            mouse_position.y > 0 && mouse_position.y < SCREEN_HEIGHT)
        sprite.setPosition(mouse_position.x, mouse_position.y);
}

void Player::shoot(std::vector<std::shared_ptr<Bullet>> &bullets, float elapsed_time)
{
    ShootAction::shoot(bullets, sprite.getPosition(), elapsed_time, (damage > 1? damage : 1));
}

void Player::setBulletsTypes(std::vector<BulletType> bt, float cd)
{
    bullets_types.clear();
    for(auto b : bt)
        bullets_types.push_back(b);
    cooldown = cd;
}

int Player::getHealth()
{
    return health;
}

bool Player::takeHealth()
{
    if(immortal_time > 0)
        return true;
    health--;
    immortal_time = IMMORTAL_TIME;
    sprite.setTexture(immortal_texture);
    set_texture_normal = true;
    return health > 0;
}

void Player::addHealth()
{
    health++;
}

void Player::increaseDmg(int value)
{
    damage += value;
}

void Player::multiplyDmg(float value)
{
    damage *= value;
}
