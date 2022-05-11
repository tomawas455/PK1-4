#include "bullets.h"
#include "constants.h"

BulletType::BulletType(BulletRotationType rt, sf::Vector2f dir, sf::Texture &t, int rot):
    rotation_type(rt), direction(dir), texture(t), rotation(rot)
{}

sf::Vector2f BulletType::getDirection()
{
    return direction;
}

int BulletType::getRotation()
{
    return rotation;
}

BulletRotationType BulletType::getRotationType()
{
    return rotation_type;
}

int BulletType::getSpeed()
{
    return speed;
}

sf::Texture& BulletType::getTexture()
{
    return texture;
}

Bullet::Bullet(sf::Vector2f &pos, BulletType bt):
    GameElement(bt.getTexture(), pos), bullet_type(bt), rotation(bt.getRotation())
{
    if(bt.getRotationType() == BulletRotationType::CONSTANT)
        sprite.setRotation(rotation);
}

void Bullet::update(float elapsed_time)
{
    sf::Vector2f vec = bullet_type.getDirection();
    sprite.move(vec.x * elapsed_time, vec.y * elapsed_time);
    if(bullet_type.getRotationType() == BulletRotationType::ROTATING)
        sprite.rotate(rotation * elapsed_time);
}

PlayerBullet::PlayerBullet(
    sf::Vector2f &pos,
    BulletType bt,
    float dmg
):Bullet(pos, bt), damage(dmg)
{}

float PlayerBullet::getDamage()
{
    return damage;
}
