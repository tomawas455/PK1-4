#ifndef SPAWNER
#define SPAWNER

#include <random>
#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "constants.h"
#include "dataManager.h"
#include "enemyData.h"
#include "powerUpsData.h"
#include "enemies.h"
#include "powerUps.h"
#include "sidebar.h"

//klasa odpowiedzialna za pojawianie się nowych przeciwników/ulepszeń na ekranie gry
class Spawner
{
    DataManager &data;
    Sidebar &sidebar;
    unsigned long next_boss_score;
    float enemies_cooldown, power_up_cooldown;

    std::vector<std::shared_ptr<Enemy>> &enemies;
    std::vector<PowerUp> &power_ups;

    std::default_random_engine generator;

    template <class T>
    std::shared_ptr<T> spawnEnemy(std::shared_ptr<EnemyData> enemy_data);
    std::vector<std::shared_ptr<GameElementAction>> getActions(
        std::vector<std::shared_ptr<GameElementAction>> &a
    );
    template <class T>
    bool addAction(
        std::vector<std::shared_ptr<GameElementAction>> &actions,
        std::shared_ptr<GameElementAction> el
    );

    sf::Vector2f getPosition();
    sf::Vector2f getDestination();

    void spawnEnemies(unsigned int score);
    void spawnNormalEnemies(unsigned int score);

    void spawnPowerUp();
    float getSpeed();
public:
    Spawner(
        DataManager &d,
        std::vector<std::shared_ptr<Enemy>> &e,
        std::vector<PowerUp> &pu,
        Sidebar &bar
    );

    void spawn(
        unsigned int score,
        float elapsed_time
    );
};

#endif
