#include "collisionsManager.h"

CollisionsManager::CollisionsManager(
    std::vector<std::shared_ptr<Enemy>> &e,
    std::vector<std::shared_ptr<Bullet>> &b,
    std::vector<PowerUp> &pu,
    Player &p,
    Sidebar &bar
): enemies(e), bullets(b), power_ups(pu), player(p), sidebar(bar)
{}

CollisionStatus CollisionsManager::check()
{
    try
    {
        checkBullets();
        checkEnemies();
        checkPowerUps();
    }
    catch(CollisionStatus &c)
    {
        return c;
    }
    return CollisionStatus::NO_COLLISION;
}

void CollisionsManager::checkBullets()
{
    std::vector<std::shared_ptr<Bullet>>::iterator b = bullets.begin(), end = bullets.end();
    while(b != end)
    {
        if(!((*b)->onScreen()) || checkBullet(*b) != CollisionStatus::NO_COLLISION)
        {
            b = bullets.erase(b);
            if(b == bullets.begin()) return;
            end = bullets.end();
            continue;
        }
        b++;
    }
}

CollisionStatus CollisionsManager::checkBullet(std::shared_ptr<Bullet> b)
{
    sf::FloatRect bulletRect = b->getGlobalBounds();
    std::shared_ptr<PlayerBullet> pb = std::dynamic_pointer_cast<PlayerBullet>(b);
    if(pb)
        return checkPlayerBullet(pb, bulletRect);
    else if(player.getGlobalBounds().intersects(bulletRect))
        return updatePlayerHp();
    return CollisionStatus::NO_COLLISION;
}

CollisionStatus CollisionsManager::checkPlayerBullet(std::shared_ptr<PlayerBullet> pb, sf::FloatRect &bulletRect)
{
    std::vector<std::shared_ptr<Enemy>>::iterator begin = enemies.begin(), end = enemies.end();
    for(auto e = begin; e != end; e++)
    {
        if((*e)->getGlobalBounds().intersects(bulletRect))
        {
            if((*e)->takeHealth(pb->getDamage()))
                return CollisionStatus::COLLISION;
            sidebar.updateScore((*e)->getMaxHp());
            enemies.erase(e);
            return CollisionStatus::ENEMY_DEAD;
        }
    }
    return CollisionStatus::NO_COLLISION;
}

CollisionStatus CollisionsManager::updatePlayerHp()
{
    if(!player.takeHealth())
        throw CollisionStatus::PLAYER_DEAD;
    sidebar.updateHp(player);
    return CollisionStatus::COLLISION;
}

void CollisionsManager::checkEnemies()
{
    std::vector<std::shared_ptr<Enemy>>::iterator begin = enemies.begin(), end = enemies.end();
    sf::FloatRect playerRect = player.getGlobalBounds();
    for(auto e = begin; e != end; e++)
    {
        if((*e)->getGlobalBounds().intersects(playerRect) &&
                updatePlayerHp() == CollisionStatus::PLAYER_DEAD)
            throw CollisionStatus::PLAYER_DEAD;
    }
}

void CollisionsManager::checkPowerUps()
{
    std::vector<PowerUp>::iterator begin = power_ups.begin(), end = power_ups.end();
    sf::FloatRect playerRect = player.getGlobalBounds();
    for(auto pu = begin; pu != end; pu++)
    {
        if(!pu->onScreen(true))
            power_ups.erase(pu);
        else if(pu->getGlobalBounds().intersects(playerRect))
        {
            applyPowerUp(pu->getType());
            power_ups.erase(pu);
        }
    }
}

void CollisionsManager::applyPowerUp(std::shared_ptr<PowerUpType> pt)
{
    if(std::dynamic_pointer_cast<HealthPowerUp>(pt))
    {
        player.addHealth();
        sidebar.updateHp(player);
        return;
    }
    std::shared_ptr<IncreaseDamagePowerUp> idmg = std::dynamic_pointer_cast<IncreaseDamagePowerUp>(pt);
    if(idmg)
    {
        player.increaseDmg(idmg->getValue());
        return;
    }
    std::shared_ptr<MultiplyDamagePowerUp> mdmg = std::dynamic_pointer_cast<MultiplyDamagePowerUp>(pt);
    if(mdmg)
    {
        player.multiplyDmg(mdmg->getValue());
        return;
    }
    std::shared_ptr<BulletPowerUp> b = std::dynamic_pointer_cast<BulletPowerUp>(pt);
    if(b)
    {
        player.setBulletsTypes(b->getBulletsTypes(), b->getCooldown());
        return;
    }
}
