#include "enemies.h"
#include <vector>
#include <SFML/Graphics.hpp>

#include "additionalUtilities.h"

Enemy::Enemy(
    sf::Texture &t,
    sf::Vector2f &pos,
    sf::Vector2f dest,
    int hp,
    std::vector<std::shared_ptr<GameElementAction>> a
): GameElement(t, pos), destination(dest), health(hp), maxHealth(hp), actions(a), on_position(false)
{}

void Enemy::update(std::vector<std::shared_ptr<Bullet>> &bullets, float elapsed_time)
{
    if(!on_position)
        move(elapsed_time);
    for(auto a = actions.begin(); a != actions.end(); a++)
    {
        std::shared_ptr<ShootAction> sa = std::dynamic_pointer_cast<ShootAction>(*a);
        if(sa)
            sa->shoot(bullets, sprite.getPosition(), elapsed_time);
        else if(on_position)
        {
            std::shared_ptr<EnemyMoveAction> ma = std::dynamic_pointer_cast<EnemyMoveAction>(*a);
            if(ma)
                ma->move(sprite, destination, elapsed_time);
        }
    }
}

void Enemy::move(float elapsed_time)
{
    sf::Vector2f position = sprite.getPosition();
    sf::Vector2f new_position = getNewPosition(position, destination, elapsed_time);
    sprite.setPosition(new_position);
    if(new_position == destination)
        on_position = true;
}

bool Enemy::takeHealth(float damage)
{
    health -= damage;
    return health > 0;
}

int Enemy::getMaxHp()
{
    return maxHealth;
}

Boss::Boss(
    sf::Texture &t,
    sf::Vector2f &pos,
    sf::Vector2f dest,
    int hp,
    std::vector<std::shared_ptr<GameElementAction>> a
):Enemy(t, pos, dest, hp, a)
{}

int Boss::getHp()
{
    return health;
}
