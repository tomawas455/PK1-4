#include "spawner.h"
#include <chrono>
#include <cmath>

#include "constants.h"

Spawner::Spawner(
    DataManager &d,
    std::vector<std::shared_ptr<Enemy>> &e,
    std::vector<PowerUp> &pu,
    Sidebar &bar
):
    data(d), next_boss_score(FIRST_BOSS_SCORE), enemies(e),
    power_ups(pu), enemies_cooldown(0), power_up_cooldown(0),
    sidebar(bar),
    generator(std::chrono::system_clock::now().time_since_epoch().count())
{}

void Spawner::spawn(
    unsigned int score,
    float elapsed_time
) {
    enemies_cooldown += elapsed_time;
    power_up_cooldown += elapsed_time;
    if(enemies_cooldown >= ENEMY_SPAWN_COOLDOWN)
    {
        enemies_cooldown -= ENEMY_SPAWN_COOLDOWN;
        spawnEnemies(score);
    }
    if(power_up_cooldown >= POWER_UP_COOLDOWN)
    {
        power_up_cooldown -= POWER_UP_COOLDOWN;
        spawnPowerUp();
    }
}

void Spawner::spawnEnemies(unsigned int score)
{
    if(score >= next_boss_score)
    {
        next_boss_score = FIRST_BOSS_SCORE + next_boss_score * 1.5;
        std::shared_ptr<Boss> boss = spawnEnemy<Boss>(data.getBoss());
        sidebar.setBoss(boss);
    }
    else
        spawnNormalEnemies(score);
}

template <class T>
std::shared_ptr<T> Spawner::spawnEnemy(std::shared_ptr<EnemyData> enemy_data)
{
    sf::Vector2f position = getPosition(), destination = getDestination();
    std::vector<std::shared_ptr<GameElementAction>> actions = getActions(enemy_data->getActions());
    std::shared_ptr<T> enemy = std::make_shared<T>(T(
        enemy_data->getTexture(),
        position,
        destination,
        enemy_data->getHp(),
        actions
    ));
    enemies.push_back(enemy);
    return enemy;
}

std::vector<std::shared_ptr<GameElementAction>> Spawner::getActions(
    std::vector<std::shared_ptr<GameElementAction>> &a
) {
    std::vector<std::shared_ptr<GameElementAction>> actions;
    for(auto el = a.begin(); el != a.end(); el++)
    {
        if(!addAction<ShootAction>(actions, *el))
            addAction<EnemyMoveAction>(actions, *el);
    }
    return actions;
}

template <class T>
bool Spawner::addAction(
    std::vector<std::shared_ptr<GameElementAction>> &actions,
    std::shared_ptr<GameElementAction> el
) {
    std::shared_ptr<T> a = std::dynamic_pointer_cast<T>(el);
    if(a)
        actions.push_back(std::make_shared<T>(T(a)));
    else
        return false;
    return true;
}

sf::Vector2f Spawner::getPosition()
{
    std::uniform_int_distribution<int> range(10, GAME_WIDTH - 50);
    return sf::Vector2f(range(generator), -32.0);
}

sf::Vector2f Spawner::getDestination()
{
    std::uniform_int_distribution<int> x_range(10, GAME_WIDTH - 50);
    std::uniform_int_distribution<int> y_range(50, ENEMY_MAX_HEIGHT - 64);
    return sf::Vector2f(x_range(generator), y_range(generator));
}

void Spawner::spawnNormalEnemies(unsigned int score)
{
    int enemies_amount = 1 + round(score/NEXT_ENEMY_SPAWN_SCORE);
    for(int i=0; i < enemies_amount; i++)
        spawnEnemy<Enemy>(data.getEnemy());
}

void Spawner::spawnPowerUp()
{
    sf::Vector2f position = getPosition();
    std::shared_ptr<PowerUpData> pu = data.getPowerUp();
    power_ups.push_back(PowerUp(
        pu->getTexture(),
        position,
        getSpeed(),
        pu->getType()
    ));
}

float Spawner::getSpeed()
{
    std::uniform_real_distribution<float> range(POWER_UP_MIN_SPEED, POWER_UP_MAX_SPEED);
    return range(generator);
}
