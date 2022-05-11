#include "gameOver.h"
#include <string>

#include "constants.h"

GameOver::GameOver(sf::Font &f,int level,int score):gameOverLabel("Game Over",f,sf::Vector2i(SCREEN_WIDTH/2.0f,40.0f),0.5,100),\
                                                    levelLabel("Level: ",f,sf::Vector2i(SCREEN_WIDTH/2.0f,200),0.5,40,sf::Color::White,std::to_string(level)),\
                                                    exitLabel("Exit",f,sf::Vector2i(SCREEN_WIDTH/2.0f,400),0.5,30)
{
    std::string s=std::to_string(score);
    scoreLabel=new DataLabel("Score: ",f,sf::Vector2i(SCREEN_WIDTH/2.0f,250),0.5,50,sf::Color::White,std::string(SCORE_DIGITS-s.length(),'0')+s);
}

GameOver::~GameOver()
{
    delete scoreLabel;
}

void GameOver::display(sf::RenderWindow &window)
{
    while(true)
    {
        sf::Event event;
        while(window.pollEvent(event))
            if(event.type == sf::Event::Closed)
                return;
        sf::Vector2i mouse=sf::Mouse::getPosition(window);
        bool leftButtonPressed=sf::Mouse::isButtonPressed(sf::Mouse::Left);
        exitLabel.update(mouse);
        if(leftButtonPressed && exitLabel.isHovered())
            return;
        draw(window);
    }
}

void GameOver::draw(sf::RenderWindow &window)
{
    window.clear();
    window.draw(gameOverLabel);
    window.draw(levelLabel);
    window.draw(*scoreLabel);
    window.draw(exitLabel);
    window.display();
}
