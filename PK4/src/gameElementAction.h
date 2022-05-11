#ifndef GAME_ELEMENT_ACTION
#define GAME_ELEMENT_ACTION

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "bullets.h"

// klasa główna akcji GameElement
class GameElementAction
{
public:
    virtual ~GameElementAction(){}
};

// akcja strzału pocisku
class ShootAction: public GameElementAction
{
    float elapsed;
protected:
    std::vector<BulletType> bullets_types;
    float cooldown;
public:
    ShootAction(std::vector<BulletType> bt, float cd);
    ShootAction(std::shared_ptr<ShootAction> sa);

    void shoot(
        std::vector<std::shared_ptr<Bullet>> &bullets,
        sf::Vector2f position,
        float elapsed_time,
        float damage = 0
    );
};

// akcja poruszania się przeciwnika
class EnemyMoveAction: public GameElementAction
{
    int current_path_id;
    std::vector<sf::Vector2f> path;
    sf::Vector2f getDestination(sf::Vector2f &pos, sf::Vector2f &def_pos);
    void updateCurrentPathId();
    bool positionOk(sf::Vector2f &pos);
public:
    EnemyMoveAction(std::vector<sf::Vector2f> &pth);
    EnemyMoveAction(std::shared_ptr<EnemyMoveAction> ma);

    void move(sf::Sprite &sprite, sf::Vector2f &def_pos, float elapsed_time);
};

#endif
