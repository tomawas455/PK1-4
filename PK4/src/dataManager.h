#ifndef DATA_MANAGER
#define DATA_MANAGER
#include <vector>
#include <map>
#include <string>
#include <filesystem>
#include <random>
#include <memory>
#include <SFML/Graphics.hpp>

#include "enemyData.h"
#include "powerUpsData.h"
#include "bullets.h"

// klasa do wczytywania/zarządzania danymi z plików
class DataManager
{
    std::unordered_map<std::string, sf::Texture> enemies_textures;
    std::unordered_map<std::string, sf::Texture> bullets_textures;
    std::unordered_map<std::string, sf::Texture> power_ups_textures;

    sf::Texture player_texture, player_immortal_texture;
    std::vector<BulletType> player_bullets_types;
    float player_bullets_cooldown;

    std::vector<std::shared_ptr<EnemyData>> enemies_data;
    std::vector<int> bosses_ids;
    std::vector<std::shared_ptr<PowerUpData>> power_ups_data;

    std::default_random_engine generator;

    void loadTextures();
    void loadTexturesInDir(std::string path, std::unordered_map<std::string, sf::Texture> &textures);
    sf::Texture getTexture(std::filesystem::path path);

    template <class T, class U>
    void load(
        BulletsTypesCreator &btc,
        std::unordered_map<std::string, sf::Texture> &t,
        std::string path,
        U &vector_data
    );
    void loadBossesIds();
    void loadPlayerShootAction(BulletsTypesCreator &btc);
public:
    DataManager();

    std::shared_ptr<EnemyData> getEnemy();
    std::shared_ptr<EnemyData> getBoss();
    std::shared_ptr<PowerUpData> getPowerUp();

    sf::Texture& getPlayerTexture();
    sf::Texture& getPlayerImmortalTexture();
    std::vector<BulletType> getPlayerBulletsTypes();
    float getPlayerBulletsCooldown();
};
#endif
