#include "tiles.h"

GameTile::GameTile(sf::Texture &t,sf::Vector2i pos,tileTypes tt)
{
    sprite.setTexture(t);
    sprite.setPosition(pos.x,pos.y);
    tileType=tt;
}

void GameTile::draw(sf::RenderTarget &target,sf::RenderStates states) const
{
    target.draw(sprite,states);
}

void Boulder::update(CollidableTile ***tiles,TexturesContainer &tc,int tileX,int tileY)
{
    if(tileY>=TILES_VERT-1) return;
    GameTile::tileTypes bottomTileType=tiles[tileX][tileY+1]->getType();
    if(!onFallableTile(bottomTileType)) return;
    sf::Texture &emptyTexture=tc.getEmpty();
    if(fellDown(tiles,emptyTexture,tileX,tileY,bottomTileType)) return;
    if(fellSide(tiles,emptyTexture,tileX,tileY,-1,0)) return;
    if(fellSide(tiles,emptyTexture,tileX,tileY,1,TILES_HORIZ)) return;
}

bool Boulder::onFallableTile(GameTile::tileTypes &tt)
{
    return tt==GameTile::tileTypes::EMPTY || tt==GameTile::tileTypes::BOULDER || tt==GameTile::tileTypes::LAVA;
}

bool Boulder::fellDown(CollidableTile ***tiles,sf::Texture &emptyTexture,int tileX,int tileY,GameTile::tileTypes &bottomTileType)
{
    if(canFall(bottomTileType))
    {
        move(tiles,tileX,tileY+1,tileX,tileY,emptyTexture);
        return true;
    }
    return false;
}

void Boulder::move(CollidableTile ***tiles,int destinationX,int destinationY,int &posX,int &posY,sf::Texture &emptyTexture)
{
    sf::Vector2i pos(sprite.getPosition());
    delete tiles[destinationX][destinationY];
    tiles[destinationX][destinationY]=tiles[posX][posY];
    tiles[posX][posY]=new Empty(emptyTexture,pos);
    setPosition(destinationX*TILE_SIZE,destinationY*TILE_SIZE);
}

void Boulder::setPosition(int x,int y)
{
    sprite.setPosition(x,y+STATUSBAR_HEIGHT);
}

bool Boulder::fellSide(CollidableTile ***tiles,sf::Texture &emptyTexture,int tileX,int tileY,int side,int xLimit)
{
    if(tileX!=xLimit && tileY<TILES_VERT-1)
    {
        GameTile::tileTypes neighbourTile=tiles[tileX+side][tileY]->getType();
        GameTile::tileTypes neighbourDownTile=tiles[tileX+side][tileY+1]->getType();
        if(canFall(neighbourTile) && canFall(neighbourDownTile))
        {
            move(tiles,tileX+side,tileY+1,tileX,tileY,emptyTexture);
            return true;
        }
    }
    return false;
}

bool Boulder::canFall(GameTile::tileTypes &tt)
{
    return tt==GameTile::tileTypes::EMPTY || tt==GameTile::tileTypes::LAVA;
}

void Lava::update(CollidableTile ***tiles,TexturesContainer &tc,int tileX,int tileY)
{
    if(isNew){isNew=false;return;}
    sf::Texture &lavaTexture=tc.getLava();
    if(tileX) trySpilling(tiles,tileX-1,tileY,lavaTexture,true);
    if(tileX<TILES_HORIZ-1) trySpilling(tiles,tileX+1,tileY,lavaTexture,false);
    if(tileY<TILES_VERT-1) trySpilling(tiles,tileX,tileY+1,lavaTexture,false);
}

void Lava::trySpilling(CollidableTile ***tiles,int x,int y,sf::Texture &lavaTexture,bool isN)
{
    if(canSpill(tiles[x][y]->getType()))
        spill(tiles,x,y,lavaTexture,isN);
}

bool Lava::canSpill(GameTile::tileTypes tt)
{
    return tt==GameTile::tileTypes::EMPTY || tt==GameTile::tileTypes::PLAYER;
}

void Lava::spill(CollidableTile ***tiles,int x,int y,sf::Texture &lavaTexture,bool isN)
{
    delete tiles[x][y];
    tiles[x][y]=new Lava(lavaTexture,sf::Vector2i(x*TILE_SIZE,y*TILE_SIZE+STATUSBAR_HEIGHT),isN);
}
