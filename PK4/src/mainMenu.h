#ifndef MAIN_MENU
#define MAIN_MENU
#define MENU_OPTIONS 2

#include <SFML/Graphics.hpp>
#include <memory>
#include "labels.h"

// Klasa reprezuntująca menu główne gry.
class MainMenu
{
    Label title;
    std::unique_ptr<ClickableLabel> options[MENU_OPTIONS];

    // Metoda rysująca w oknie napisy menu głównego.
    void draw(sf::RenderWindow &window);
public:
    // Konstruktor tworzący odpowiednie napisy do menu głównego.
    MainMenu(sf::Font &font);

    // Enum informujący którą opcję gracz wybrał w menu głównym.
    enum choice{START=0,EXIT};

    // Metoda wyświetlająca menu główne
    choice display(sf::RenderWindow &window);
};
#endif
