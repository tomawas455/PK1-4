#include "statusbar.h"
#include <string>

#include "constants.h"

Statusbar::Statusbar(sf::Font &f):levelLabel("level: ",f,sf::Vector2i(5,1),0,12,sf::Color::White,"1"),\
                                  gemsLabel(" Gems",f,sf::Vector2i(150,1),0,12,sf::Color::White,"0",true),\
                                  timeLabel("s",f,sf::Vector2i(SCREEN_WIDTH/2,6),0.5,12,sf::Color::White,std::to_string(LEVEL_TIME),true),\
                                  scoreLabel("score: ",f,sf::Vector2i(SCREEN_WIDTH-5,10),1,12,sf::Color::White,std::string(SCORE_DIGITS,'0')),\
                                  level(1),\
                                  gems(0),\
                                  time(LEVEL_TIME),\
                                  score(0)
{
    line[0].position=sf::Vector2f(0,STATUSBAR_HEIGHT);
    line[1].position=sf::Vector2f(SCREEN_WIDTH,STATUSBAR_HEIGHT);
    line[0].color=sf::Color::White;
    line[1].color=sf::Color::White;
}

void Statusbar::draw(sf::RenderTarget &target,sf::RenderStates states) const
{
    target.draw(line,2,sf::Lines);
    target.draw(levelLabel);
    target.draw(gemsLabel);
    target.draw(timeLabel);
    target.draw(scoreLabel);
}

void Statusbar::addLevel()
{
    levelLabel.updateData(std::to_string(++level));
}

void Statusbar::addGem()
{
    gemsLabel.updateData(std::to_string(++gems));
    score+=GEM_SCORE_BASE+(LEVEL_TIME-time)/10;
    std::string s=std::to_string(score);
    scoreLabel.updateData(std::string(SCORE_DIGITS-s.length(),'0')+s);
}


void Statusbar::resetGems()
{
    gems=0;
    gemsLabel.updateData(std::to_string(gems));
}
void Statusbar::resetTime()
{
    time=LEVEL_TIME;
    timeLabel.updateData(std::to_string(LEVEL_TIME));
}

bool Statusbar::isTime(float elapsed)
{
    time-=elapsed;
    timeLabel.updateData(std::to_string((int)time));
    return time>0;
}
