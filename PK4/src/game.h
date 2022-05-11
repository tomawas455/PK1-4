#ifndef GAME
#define GAME

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "player.h"
#include "sidebar.h"
#include "spawner.h"
#include "collisionsManager.h"
#include "enemies.h"
#include "bullets.h"
#include "powerUps.h"
#include "dataManager.h"

//Klasa zarządzająca rozgrywką.
class Game
{
    DataManager data;
    Sidebar bar;
    Player player;
    Spawner spawner;
    CollisionsManager collisions_manager;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Bullet>> bullets;
    std::vector<PowerUp> power_ups;

    sf::Font &font;
    enum states {PLAY, OVER, EXIT};
    states state;

    void draw(sf::RenderWindow &window);
public:
    Game(sf::Font &f);

    void run(sf::RenderWindow &window);
};

#endif
