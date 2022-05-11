#include "powerUps.h"

IncreaseDamagePowerUp::IncreaseDamagePowerUp(int val): value(val)
{}

MultiplyDamagePowerUp::MultiplyDamagePowerUp(float val): value(val)
{}

int IncreaseDamagePowerUp::getValue()
{
    return value;
}

float MultiplyDamagePowerUp::getValue()
{
    return value;
}

BulletPowerUp::BulletPowerUp(std::vector<BulletType> bt, float cd): bullets_types(bt), cooldown(cd)
{}

std::vector<BulletType> BulletPowerUp::getBulletsTypes()
{
    return bullets_types;
}

float BulletPowerUp::getCooldown()
{
    return cooldown;
}

PowerUp::PowerUp(
    sf::Texture &t,
    sf::Vector2f pos,
    float spd,
    std::shared_ptr<PowerUpType> pt
): GameElement(t, pos), speed(spd), pu_type(pt)
{}

void PowerUp::update(float elapsed_time)
{
    sprite.move(0.0, speed * elapsed_time);
}

std::shared_ptr<PowerUpType> PowerUp::getType()
{
    return pu_type;
}
