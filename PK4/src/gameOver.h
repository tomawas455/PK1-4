#ifndef GAME_OVER
#define GAME_OVER

#include <SFML/Graphics.hpp>
#include <memory>
#include "labels.h"

// Klasa reprezentująca ekran końca gry
class GameOver
{
private:
    Label gameOverLabel;
    ClickableLabel exitLabel;
    std::unique_ptr<DataLabel> scoreLabel;

    // Metoda rysująca elementy ekranu końca gry
    void draw(sf::RenderWindow &window);
public:
    // Konstruktor, który tworzy odpowiednie napisy.
    GameOver(sf::Font &f,int score);

    // Metoda wyświetlająca ekran końca gry.
    void display(sf::RenderWindow &window);
};
#endif
