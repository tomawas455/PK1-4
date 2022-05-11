#ifndef ENEMY_DATA
#define ENEMY_DATA
#include <vector>
#include <map>
#include <string>
#include <filesystem>
#include <memory>
#include <SFML/Graphics.hpp>

#include "bullets.h"
#include "enemies.h"
#include "bulletsTypesCreator.h"
#include "gameElementAction.h"

#include "json.hpp"
using json = nlohmann::json;

// klasa zawierająca informację o przeciwniku który może się pojawić w grze
class EnemyData
{
protected:
    sf::Texture &texture;
    int health;
    std::vector<std::shared_ptr<GameElementAction>> actions;
    bool boss;

    void setMoveAction(json &data, std::string &filename);
public:
    EnemyData(
        json &enemy_data,
        std::string &filename,
        std::unordered_map<std::string, sf::Texture> &enemies_textures,
        BulletsTypesCreator &btc
    );

    bool isBoss();
    sf::Texture& getTexture();
    int getHp();
    std::vector<std::shared_ptr<GameElementAction>>& getActions();
};
#endif
