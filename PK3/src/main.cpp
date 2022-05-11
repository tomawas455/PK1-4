#include <iostream>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "mainMenu.h"
#include "game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"PROJEKT - Boulder Dash");
    sf::Font font;
    font.loadFromFile("data/DejaVuSansMono.ttf");
    MainMenu::choice menuChoice;
    do
    {
        menuChoice=MainMenu(font).display(window);
        if(menuChoice==MainMenu::choice::START)
            Game(font).display(window);
    }while(menuChoice!=MainMenu::choice::EXIT);
    return 0;
}
