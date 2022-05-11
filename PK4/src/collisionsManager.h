#ifndef COLLISIONS_MANAGER
#define COLLISIONS_MANAGER

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "sidebar.h"
#include "enemies.h"
#include "bullets.h"
#include "powerUps.h"
#include "player.h"

enum CollisionStatus{NO_COLLISION, COLLISION, PLAYER_DEAD, ENEMY_DEAD};

// klasa do zarządzania kolizją
class CollisionsManager
{
    Sidebar &sidebar;
    Player &player;

    std::vector<std::shared_ptr<Enemy>> &enemies;
    std::vector<std::shared_ptr<Bullet>> &bullets;
    std::vector<PowerUp> &power_ups;

    void checkBullets();
    CollisionStatus checkBullet(std::shared_ptr<Bullet> b);
    CollisionStatus checkPlayerBullet(std::shared_ptr<PlayerBullet> pb, sf::FloatRect &bulletRec);
    CollisionStatus updatePlayerHp();
    void checkEnemies();
    void checkPowerUps();
    void applyPowerUp(std::shared_ptr<PowerUpType> pt);
public:
    CollisionsManager(
        std::vector<std::shared_ptr<Enemy>> &e,
        std::vector<std::shared_ptr<Bullet>> &b,
        std::vector<PowerUp> &pu,
        Player &p,
        Sidebar &bar
    );
    CollisionStatus check();
};
#endif
