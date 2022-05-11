#ifndef POWER_UPS_DATA
#define POWER_UPS_DATA

#include <vector>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "bullets.h"
#include "powerUps.h"
#include "bulletsTypesCreator.h"

#include "json.hpp"
using json = nlohmann::json;

// klasa zawierająca informację o ulepszeniu które może się pojawić w grze
class PowerUpData
{
    sf::Texture &texture;
    std::shared_ptr<PowerUpType> power_up_type;
public:
    PowerUpData(
        json &data,
        std::string &filename,
        std::unordered_map<std::string, sf::Texture> &textures,
        BulletsTypesCreator &btc
    );

    sf::Texture& getTexture();
    std::shared_ptr<PowerUpType> getType();
};

#endif
