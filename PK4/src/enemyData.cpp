#include "enemyData.h"
#include "additionalUtilities.h"

EnemyData::EnemyData(
    json &enemy_data,
    std::string &filename,
    std::unordered_map<std::string, sf::Texture> &enemies_textures,
    BulletsTypesCreator &btc
):
    health(getValueFromJson(enemy_data, "health", filename)),
    texture(getTextureByFilename(getValueFromJson(enemy_data, "texture", filename), enemies_textures, filename)),
    boss(getValueFromJson(enemy_data, "boss", filename))
{
    setMoveAction(enemy_data, filename);
    if(enemy_data.contains("bullets"))
        actions.push_back(std::make_shared<ShootAction>(ShootAction(
            btc.createBulletsTypes(enemy_data, filename),
            getValueFromJson(enemy_data, "cooldown", filename)
        )));
}

void EnemyData::setMoveAction(json &data, std::string &filename)
{
    if(!data.contains("path"))
        return;
    if(!(data["path"].is_array()))
        throw GameException("There is path, but it's not array in file: "+filename);
    std::vector<sf::Vector2f> path;
    for(auto &el : data["path"])
        path.push_back(getDirection(el, filename));
    actions.push_back(std::make_shared<EnemyMoveAction>(EnemyMoveAction(path)));
}

bool EnemyData::isBoss()
{
    return boss;
}

sf::Texture& EnemyData::getTexture()
{
    return texture;
}

int EnemyData::getHp()
{
    return health;
}

std::vector<std::shared_ptr<GameElementAction>>& EnemyData::getActions()
{
    return actions;
}
