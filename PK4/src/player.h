#ifndef PLAYER
#define PLAYER

#include <vector>
#include <SFML/Graphics.hpp>

#include "additionalUtilities.h"
#include "gameElementAction.h"
#include "bullets.h"

// klasa reprezetująca gracza/ zarządzająca graczem
class Player: public GameElement, public ShootAction
{
    int health;
    float damage, immortal_time;
    sf::Texture &normal_texture, &immortal_texture;
    bool set_texture_normal;

    void shoot(std::vector<std::shared_ptr<Bullet>> &bullets, float elapsed_time);
public:
    Player(sf::Texture &t, sf::Texture &it, std::vector<BulletType> bt, float cooldown);

    void update(sf::Vector2i mouse_position, std::vector<std::shared_ptr<Bullet>> &bullets, float elapsed_time);

    void move(sf::Vector2i mouse_position);
    void setBulletsTypes(std::vector<BulletType> bt, float cd);

    int getHealth();
    bool takeHealth();
    void addHealth();

    void increaseDmg(int value);
    void multiplyDmg(float value);
};

#endif
