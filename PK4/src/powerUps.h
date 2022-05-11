#ifndef POWER_UPS
#define POWER_UPS

#include "additionalUtilities.h"
#include "bullets.h"

// główna klasa powerupa
class PowerUpType
{
public:
    virtual ~PowerUpType(){}
};

// klasa reprezentująca ulepszenie dodające obrażenia
class IncreaseDamagePowerUp: public PowerUpType
{
    int value;
public:
    IncreaseDamagePowerUp(int val);

    int getValue();
};

// klasa reprezentująca ulepszenie mnożące obrażenia
class MultiplyDamagePowerUp: public PowerUpType
{
    float value;
public:
    MultiplyDamagePowerUp(float val);

    float getValue();
};

// klasa reprezentująca ulepszenie dodające punkt życia
class HealthPowerUp: public PowerUpType
{
};

// klasa reprezentująca ulepszenie zmieniające typ wystrzeliwanych pocisków
class BulletPowerUp: public PowerUpType
{
    std::vector<BulletType> bullets_types;
    float cooldown;
public:
    BulletPowerUp(std::vector<BulletType> bt, float cd);

    std::vector<BulletType> getBulletsTypes();
    float getCooldown();
};

// klasa reprezentująca power up na ekranie gry
class PowerUp: public GameElement
{
    std::shared_ptr<PowerUpType> pu_type;
    float speed;
public:
    PowerUp(
        sf::Texture &t,
        sf::Vector2f pos,
        float spd,
        std::shared_ptr<PowerUpType> pt
    );
    void update(float elapsed_time);
    std::shared_ptr<PowerUpType> getType();
};

#endif
