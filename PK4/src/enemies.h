#ifndef ENEMIES
#define ENEMIES

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "additionalUtilities.h"
#include "gameElementAction.h"
#include "bullets.h"

// klasa reprezentująca przeciwnika
class Enemy: public GameElement
{
    int maxHealth;
    sf::Vector2f destination;
    std::vector<std::shared_ptr<GameElementAction>> actions;
    bool on_position;
    void move(float elapsed_time);
protected:
    int health;
public:
    Enemy(
        sf::Texture &t,
        sf::Vector2f &pos,
        sf::Vector2f dest,
        int hp,
        std::vector<std::shared_ptr<GameElementAction>> a
    );
    void update(std::vector<std::shared_ptr<Bullet>> &bullets, float elapsed_time);

    bool takeHealth(float damage);

    int getMaxHp();
};

// klasa reprezentująca bossa
class Boss: public Enemy
{
public:
    Boss(
        sf::Texture &t,
        sf::Vector2f &pos,
        sf::Vector2f dest,
        int hp,
        std::vector<std::shared_ptr<GameElementAction>> a
    );
    int getHp();
};

#endif
