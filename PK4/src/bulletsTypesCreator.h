#ifndef BULLETS_TYPES_CREATOR
#define BULLETS_TYPES_CREATOR

#include <string>
#include <map>
#include <vector>

#include "json.hpp"
using json = nlohmann::json;

#include "gameElementAction.h"
#include "additionalUtilities.h"
#include "bullets.h"

//klasa do tworzenia typów pocisków z zmiennej typu json
class BulletsTypesCreator
{
    std::unordered_map<std::string, sf::Texture> &bullets_textures;

    BulletRotationType getBulletRotationType(std::string bt, std::string &filename);
public:
    BulletsTypesCreator(std::unordered_map<std::string, sf::Texture> &bt);
    std::vector<BulletType> createBulletsTypes(
        json &data,
        std::string &filename
    );
};

#endif
