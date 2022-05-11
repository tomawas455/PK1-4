#include "game.h"
#include <string>
#include <chrono>

#include "gameOver.h"

Game::Game(sf::Font &f):bar(f),textures(),font(f)
{
    font=f;
    tiles=nullptr;
    player=new Player(textures.getPlayer(),sf::Vector2i(0,STATUSBAR_HEIGHT));
    state=Game::states::PLAY;
}

Game::~Game()
{
    if(tiles)
    {
        for(int i=0;i<TILES_HORIZ;i++)
        {
            for(int j=0;j<TILES_VERT;j++)
                delete tiles[i][j];
            delete [] tiles[i];
        }
        delete [] tiles;
    }
    delete player;
}

void Game::display(sf::RenderWindow &window)
{
    createTiles();
    sf::Clock clock;
    do
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                state=states::EXIT;
            else if(event.type==sf::Event::KeyReleased && player->move(tiles,event))
            {
                updateElements();
                collisionEffect();
            }
        }
        if(!bar.isTime(clock.restart().asSeconds())) state=Game::states::OVER;
        draw(window);
    }while(state==states::PLAY);
    if(state==states::OVER) GameOver(font,bar.getLevel(),bar.getScore()).display(window);
}

void Game::createTiles()
{
    resetMap();
    int level=bar.getLevel();
    int seed=std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine randomEngine(seed);
    generateBoulders(BOULDERS_BASE+level*BOULDERS_PER_LEVEL,randomEngine);
    generateLava(LAVA_BASE+level*LAVA_PER_LEVEL,randomEngine);
    generateGems(GEMS_AMOUNT,randomEngine);
    generateExit(randomEngine);
    generatePlayer();
}

void Game::resetMap()
{
    bool generateNew=(tiles==nullptr);
    if(generateNew) tiles=new CollidableTile**[TILES_HORIZ];
    for(int i=0;i<TILES_HORIZ;i++)
    {
        if(generateNew) tiles[i]=new CollidableTile*[TILES_VERT];
        for(int j=0;j<TILES_VERT;j++)
        {
            if(!generateNew) delete tiles[i][j];
            tiles[i][j]=new Ground(textures.getGround(),sf::Vector2i(i*TILE_SIZE,STATUSBAR_HEIGHT+j*TILE_SIZE));
        }
    }
}

void Game::generateBoulders(int amount,std::default_random_engine &randomEngine)
{
    int x,y;
    for(int i=0;i<amount;i++)
    {
        getCoords(x,y,randomEngine);
        delete tiles[x][y];
        tiles[x][y]=new Boulder(textures.getBoulder(),sf::Vector2i(x*TILE_SIZE,STATUSBAR_HEIGHT+y*TILE_SIZE));
    }
}

void Game::getCoords(int &x,int &y,std::default_random_engine &randomEngine)
{

    x=randomEngine()%TILES_HORIZ;
    y=randomEngine()%TILES_VERT;
    while(x<2 || y<2 || tiles[x][y]->getType()!=GameTile::tileTypes::GROUND)
    {
        x=randomEngine()%TILES_HORIZ;
        y=randomEngine()%TILES_VERT;
    }
}

void Game::generateLava(int amount,std::default_random_engine &randomEngine)
{
    int x,y;
    for(int i=0;i<amount;i++)
    {
        getCoords(x,y,randomEngine);
        delete tiles[x][y];
        tiles[x][y]=new Lava(textures.getLava(),sf::Vector2i(x*TILE_SIZE,STATUSBAR_HEIGHT+y*TILE_SIZE));
    }
}

void Game::generateGems(int amount,std::default_random_engine &randomEngine)
{
    int x,y;
    for(int i=0;i<amount;i++)
    {
        getCoords(x,y,randomEngine);
        delete tiles[x][y];
        tiles[x][y]=new Gem(textures.getGem(),sf::Vector2i(x*TILE_SIZE,STATUSBAR_HEIGHT+y*TILE_SIZE));
    }
}

void Game::generateExit(std::default_random_engine &randomEngine)
{
    int x,y;
    getCoords(x,y,randomEngine);
    delete tiles[x][y];
    tiles[x][y]=new Exit(textures.getExit(),sf::Vector2i(x*TILE_SIZE,STATUSBAR_HEIGHT+y*TILE_SIZE));
}

void Game::generatePlayer()
{
    delete tiles[0][0];
    tiles[0][0]=new Empty(textures.getEmpty(),sf::Vector2i(0,STATUSBAR_HEIGHT));
    player->setPosition(sf::Vector2i(0,STATUSBAR_HEIGHT));
}

void Game::updateElements()
{
    for(int j=TILES_VERT-1;j>=0;j--)
        for(int i=TILES_HORIZ-1;i>=0;i--)
            tiles[i][j]->update(tiles,textures,i,j);
}

void Game::collisionEffect()
{
    sf::Vector2i playerTile=player->getTile();
    CollidableTile **t=&(tiles[playerTile.x][playerTile.y]);
    switch((*t)->getColEffect())
    {
        case CollidableTile::collisionEffects::DESTROY_ELEMENT:
            delete *t;
            *t=new Empty(textures.getEmpty(),sf::Vector2i(playerTile.x*TILE_SIZE,playerTile.y*TILE_SIZE));
            break;
        case CollidableTile::collisionEffects::ADD_POINTS:
            bar.addGem();
            delete *t;
            *t=new Empty(textures.getEmpty(),sf::Vector2i(playerTile.x*TILE_SIZE,playerTile.y*TILE_SIZE));
            break;
        case CollidableTile::collisionEffects::NEXT_LEVEL:
            bar.addLevel();
            bar.resetGems();
            bar.resetTime();
            createTiles();
            break;
        case CollidableTile::collisionEffects::END_GAME:
            state=states::OVER;
            break;
        default:
            break;
    }
}

void Game::draw(sf::RenderWindow &window)
{
    window.clear();
    window.draw(bar);
    for(int i=0;i<TILES_HORIZ;i++)
        for(int j=0;j<TILES_VERT;j++)
            window.draw(*(tiles[i][j]));
    window.draw(*player);
    window.display();
}
