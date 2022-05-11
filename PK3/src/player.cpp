#include "player.h"
#include "constants.h"

void Player::setPosition(sf::Vector2i newPosition)
{
    sprite.setPosition(newPosition.x,newPosition.y);
}

bool Player::move(CollidableTile ***tiles,sf::Event &event)
{
    sf::Vector2i tile=getTile();
    switch(event.key.code)
    {
        case sf::Keyboard::W:
            if(tile.y>=1) move(tiles,tile.x,tile.y-1,0,-TILE_SIZE);
            break;
        case sf::Keyboard::S:
            if(tile.y<TILES_VERT-1) move(tiles,tile.x,tile.y+1,0,TILE_SIZE);
            break;
        case sf::Keyboard::A:
            if(tile.x>=1) move(tiles,tile.x-1,tile.y,-TILE_SIZE,0);
            break;
        case sf::Keyboard::D:
            if(tile.x<TILES_HORIZ-1) move(tiles,tile.x+1,tile.y,TILE_SIZE,0);
            break;
        default:
            return false;
    }
    return true;
}

void Player::move(CollidableTile ***tiles,int newTileX,int newTileY,int moveX,int moveY)
{
    CollidableTile *t=tiles[newTileX][newTileY];
    if(!canStandOn(t)) return;
    sprite.move(moveX,moveY);
}

bool Player::canStandOn(CollidableTile *t)
{
    GameTile::tileTypes tt=t->getType();
    return tt==GameTile::tileTypes::EMPTY || tt==GameTile::tileTypes::GROUND || tt==GameTile::tileTypes::SPECIAL;
}

sf::Vector2i Player::getTile()
{
    sf::Vector2i pos(sprite.getPosition());
    return sf::Vector2i(pos.x/TILE_SIZE,pos.y/TILE_SIZE);
}
