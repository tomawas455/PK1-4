#include "mainMenu.h"
#include <string>

#include "constants.h"

MainMenu::MainMenu(sf::Font &font):
    title("Space Shooter",font,sf::Vector2i(SCREEN_WIDTH/2.0f,40.0f),0.5,100)
{
    std::string optionsStrings[MENU_OPTIONS]={"Start","Exit"};
    for(int i=0;i<MENU_OPTIONS;i++)
        options[i]=std::make_unique<ClickableLabel>(ClickableLabel(
            optionsStrings[i],
            font,
            sf::Vector2i(SCREEN_WIDTH/2.0f,200.0f+i*80),
            0.5,50
        ));
}

MainMenu::choice MainMenu::display(sf::RenderWindow &window)
{
    while(true)
    {
        sf::Event event;
        while(window.pollEvent(event))
            if(event.type == sf::Event::Closed)
                return choice::EXIT;
        sf::Vector2i mouse=sf::Mouse::getPosition(window);
        bool leftButtonPressed=sf::Mouse::isButtonPressed(sf::Mouse::Left);
        for(int i=0;i<MENU_OPTIONS;i++)
        {
            options[i]->update(mouse);
            if(leftButtonPressed && options[i]->isHovered())
                return (choice)i;
        }
        draw(window);
    }
}

void MainMenu::draw(sf::RenderWindow &window)
{
    window.clear();
    window.draw(title);
    for(int i=0;i<MENU_OPTIONS;i++)
        window.draw(*options[i]);
    window.display();
}
