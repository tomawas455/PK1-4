#include "texturesContainer.h"

TexturesContainer::TexturesContainer()
{
    empty.loadFromFile("data/empty.png");
    ground.loadFromFile("data/ground.png");
    boulder.loadFromFile("data/boulder.png");
    lava.loadFromFile("data/lava.png");
    player.loadFromFile("data/player.png");
    gem.loadFromFile("data/gem.png");
    exit.loadFromFile("data/exit.png");
}
