#include "powerUpsData.h"

#include "additionalUtilities.h"

PowerUpData::PowerUpData(
    json &data,
    std::string &filename,
    std::unordered_map<std::string, sf::Texture> &textures,
    BulletsTypesCreator &btc
): texture(getTextureByFilename(getValueFromJson(data, "texture", filename), textures, filename))
{
    std::string pu_type = getValueFromJson(data, "type", filename);
    if(pu_type == "health")
        power_up_type = std::make_shared<HealthPowerUp>(HealthPowerUp());
    else if(pu_type == "increase damage")
        power_up_type = std::make_shared<IncreaseDamagePowerUp>(IncreaseDamagePowerUp(getValueFromJson(data, "value", filename)));
    else if(pu_type == "multiply damage")
        power_up_type = std::make_shared<MultiplyDamagePowerUp>(MultiplyDamagePowerUp(getValueFromJson(data, "value", filename)));
    else if(pu_type == "bullet")
    {
        if(!data.contains("bullets"))
            throw GameException("Missing bullets array in file: " + filename);
        power_up_type = std::make_shared<BulletPowerUp>(BulletPowerUp(
            btc.createBulletsTypes(data, filename),
            getValueFromJson(data, "cooldown", filename)
        ));
    }
    else
        throw GameException("Missing power up type in file " + filename);
}

sf::Texture& PowerUpData::getTexture()
{
    return texture;
}

std::shared_ptr<PowerUpType> PowerUpData::getType()
{
    return power_up_type;
}
