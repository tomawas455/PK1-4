#include <iostream>
#include <exception>
#include <SFML/Graphics.hpp>

#include "constants.h"
#include "mainMenu.h"
#include "game.h"

#include "dataManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "PROJEKT - Space Shooter");
    sf::Font font;
    font.loadFromFile("data/DejaVuSansMono.ttf");
    MainMenu::choice menu_choice;
    try
    {
        do
        {
            menu_choice = MainMenu(font).display(window);
            if(menu_choice == MainMenu::choice::START)
                Game(font).run(window);
        }while(menu_choice != MainMenu::choice::EXIT);
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
