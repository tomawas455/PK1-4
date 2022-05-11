#include "dataManager.h"
#include <fstream>
#include <stdexcept>
#include <chrono>
#include <algorithm>

#include "json.hpp"
using json = nlohmann::json;

#include "bulletsTypesCreator.h"
#include "additionalUtilities.h"

DataManager::DataManager():
    generator(std::chrono::system_clock::now().time_since_epoch().count())
{
    loadTextures();
    BulletsTypesCreator btc(bullets_textures);
    load<EnemyData>(btc, enemies_textures, "data/enemies", enemies_data);
    loadBossesIds();
    load<PowerUpData>(btc, power_ups_textures, "data/powerUps", power_ups_data);
    loadPlayerShootAction(btc);
}

void DataManager::loadTextures()
{
    std::string path = "data/graphics";
    loadTexturesInDir(path+"/enemies", enemies_textures);
    loadTexturesInDir(path+"/bullets", bullets_textures);
    loadTexturesInDir(path+"/powerUps", power_ups_textures);
    player_texture = getTexture(std::filesystem::path(path+"/player.png"));
    player_immortal_texture = getTexture(std::filesystem::path(path+"/player_immortal.png"));
}

void DataManager::loadTexturesInDir(
    std::string path,
    std::unordered_map<std::string, sf::Texture> &textures
) {
    for(const auto &entry : std::filesystem::directory_iterator(path))
    {
        sf::Texture t = getTexture(entry.path());
        textures[entry.path().filename()] = t;
    }
}

sf::Texture DataManager::getTexture(std::filesystem::path path)
{
    sf::Texture t;
    if(!t.loadFromFile(path))
        throw std::string("Texture loading error");
    return t;
}

template <class T, class U>
void DataManager::load(BulletsTypesCreator &btc, std::unordered_map<std::string, sf::Texture> &t, std::string path, U &vector_data)
{
    for(const auto &entry : std::filesystem::directory_iterator(path))
    {
        json j;
        std::ifstream file(entry.path());
        std::string filename = entry.path().filename();
        try
        {
            file >> j;
            file.close();
            vector_data.push_back(std::make_shared<T>(T(j, filename, t, btc)));
        }
        catch(json::parse_error& e)
        {
            file.close();
            throw GameException("json parsing error: "+std::string(e.what()));
        }
        catch(json::type_error &e)
        {
            throw GameException("invalid value, file: "+filename+", error: "+std::string(e.what()));
        }
    }
    if(!vector_data.size())
        throw GameException("Missing game files! "+std::string(typeid(T).name()));
}

void DataManager::loadBossesIds()
{
    for(int i = 0; i < enemies_data.size(); i++)
        if(enemies_data[i]->isBoss())
            bosses_ids.push_back(i);
}

void DataManager::loadPlayerShootAction(BulletsTypesCreator &btc)
{
    json j;
    std::ifstream file("data/player_default_bullets.json");
    file >> j;
    std::string filename = "player_default_bullets.json";
    if(!j.contains("bullets"))
        throw GameException("missing player default bullets, file: "+filename);
    player_bullets_cooldown = getValueFromJson(j, "cooldown", filename);
    player_bullets_types = btc.createBulletsTypes(j, filename);
}

std::shared_ptr<EnemyData> DataManager::getBoss()
{
    if(!(bosses_ids.size())) return getEnemy();
    std::uniform_int_distribution<int> range(0, bosses_ids.size() - 1);
    return enemies_data[bosses_ids[range(generator)]];
}

std::shared_ptr<EnemyData> DataManager::getEnemy()
{
    std::uniform_int_distribution<int> range(0, enemies_data.size() - 1);
    int choice;
    do
    {
        choice = range(generator);
    }while(bosses_ids.size() != enemies_data.size() &&
            std::find(bosses_ids.begin(), bosses_ids.end(), choice) != bosses_ids.end());
    return enemies_data[choice];
}

sf::Texture& DataManager::getPlayerTexture()
{
    return player_texture;
}

sf::Texture& DataManager::getPlayerImmortalTexture()
{
    return player_immortal_texture;
}

std::vector<BulletType> DataManager::getPlayerBulletsTypes()
{
    return player_bullets_types;
}

float DataManager::getPlayerBulletsCooldown()
{
    return player_bullets_cooldown;
}

std::shared_ptr<PowerUpData> DataManager::getPowerUp()
{
    std::uniform_int_distribution<int> range(0, power_ups_data.size() - 1);
    return power_ups_data[range(generator)];
}
