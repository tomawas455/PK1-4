#include "gameElementAction.h"

#include "constants.h"
#include "additionalUtilities.h"

ShootAction::ShootAction(std::vector<BulletType> bt, float cd):
    bullets_types(bt), cooldown(cd), elapsed(0)
{}

ShootAction::ShootAction(std::shared_ptr<ShootAction> sa):
    bullets_types(sa->bullets_types), cooldown(sa->cooldown), elapsed(sa->elapsed)
{}

void ShootAction::shoot(
    std::vector<std::shared_ptr<Bullet>> &bullets,
    sf::Vector2f position,
    float elapsed_time,
    float damage
) {
    elapsed += elapsed_time;
    if(elapsed < cooldown)
        return;
    elapsed -= cooldown;
    std::vector<BulletType>::iterator start = bullets_types.begin(), end = bullets_types.end();
    for(auto bt = start; bt != end; bt++)
    {
        if(damage)
            bullets.push_back(std::make_shared<PlayerBullet>(PlayerBullet(position, *bt, damage)));
        else
            bullets.push_back(std::make_shared<Bullet>(Bullet(position, *bt)));
    }
}

EnemyMoveAction::EnemyMoveAction(std::vector<sf::Vector2f> &pth):
    path(pth), current_path_id(0)
{}

EnemyMoveAction::EnemyMoveAction(std::shared_ptr<EnemyMoveAction> ma):
    path(ma->path), current_path_id(ma->current_path_id)
{}

void EnemyMoveAction::move(sf::Sprite &sprite, sf::Vector2f &def_pos, float elapsed_time)
{
    sf::Vector2f position = sprite.getPosition();
    sf::Vector2f destination = getDestination(position, def_pos);
    sf::Vector2f new_position;
    do
    {
        new_position = getNewPosition(position, destination, elapsed_time);
    }while(!positionOk(new_position));
    sprite.setPosition(new_position);
}

sf::Vector2f EnemyMoveAction::getDestination(sf::Vector2f &pos, sf::Vector2f &def_pos)
{
    if(current_path_id == -1 && pos != def_pos) return sf::Vector2f(def_pos);
    sf::Vector2f dest(def_pos);
    for(auto i = path.begin(); i != path.begin() + current_path_id + 1; i++)
    {
        sf::Vector2f pos(dest.x + i->x, dest.y + i->y);
        if(!positionOk(pos))
            continue;
        dest.x += i->x;
        dest.y += i->y;
    }
    if(pos == dest)
    {
        updateCurrentPathId();
        return getDestination(pos, def_pos);
    }
    return dest;
}

void EnemyMoveAction::updateCurrentPathId()
{
    if(current_path_id == (path.size() - 1))
        current_path_id = -1;
    else
        current_path_id++;
}

bool EnemyMoveAction::positionOk(sf::Vector2f &pos)
{
    return pos.x >= 0 && pos.x <= GAME_WIDTH &&
           pos.y >= 0 && pos.y <= ENEMY_MAX_HEIGHT;
}
