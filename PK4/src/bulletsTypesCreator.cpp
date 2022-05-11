#include "bulletsTypesCreator.h"
#include "additionalUtilities.h"

BulletsTypesCreator::BulletsTypesCreator(std::unordered_map<std::string, sf::Texture> &bt):
    bullets_textures(bt)
{}

std::vector<BulletType> BulletsTypesCreator::createBulletsTypes(
    json &data,
    std::string &filename
) {
    if(!data["bullets"].is_array())
        throw GameException("there are bullets types, but it isn't array in file "+filename);
    std::vector<BulletType> bullet_types;
    for(auto &el : data["bullets"])
    {
        if(!el.is_object())
            throw GameException("wrong bullet type in file "+filename);
        BulletType t(
            getBulletRotationType(getValueFromJson(el, "rotation type", filename), filename),
            getDirection(getValueFromJson(el, "direction", filename), filename),
            getTextureByFilename(getValueFromJson(el, "texture", filename), bullets_textures, filename),
            getValueFromJson(el, "rotation", filename)
        );
        bullet_types.push_back(t);
    }
    return bullet_types;
}

BulletRotationType BulletsTypesCreator::getBulletRotationType(std::string bt, std::string &filename)
{
    transform(bt.begin(), bt.end(), bt.begin(), ::tolower);
    if(bt == "rotating")
        return BulletRotationType::ROTATING;
    if(bt == "constant")
        return BulletRotationType::CONSTANT;
    throw GameException("\""+bt+"\" is not correct bullet rotation type, file: "+filename);
}
