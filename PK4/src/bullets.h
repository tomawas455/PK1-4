#ifndef BULLETS
#define BULLETS
#include <SFML/Graphics.hpp>
#include "additionalUtilities.h"

enum BulletRotationType {ROTATING, CONSTANT};

//Klasa reprezentująca pocisk do wystrzelenia
class BulletType
{
    BulletRotationType rotation_type;
    sf::Vector2f direction;
    int rotation, speed;
    sf::Texture &texture;
public:
    BulletType(BulletRotationType rt, sf::Vector2f dir, sf::Texture &t, int rot);
    sf::Vector2f getDirection();
    int getRotation();
    BulletRotationType getRotationType();
    int getSpeed();
    sf::Texture& getTexture();
};

// Klasa reprezentująca wystrzelony pocisk
class Bullet: public GameElement
{
    BulletType bullet_type;
    int rotation;
public:
    Bullet(sf::Vector2f &pos, BulletType bt);
    void update(float elapsed_time);
};

// klasa pocisku gracza
class PlayerBullet: public Bullet
{
    float damage;
public:
    PlayerBullet(sf::Vector2f &pos, BulletType bt, float dmg);

    float getDamage();
};
#endif
