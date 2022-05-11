/** @file */
#ifndef GAME_OVER
#define GAME_OVER

#include <SFML/Graphics.hpp>
#include "labels.h"

/** Klasa reprezentująca ekran końca gry
 */
class GameOver
{
private:
    Label gameOverLabel;
    ClickableLabel exitLabel;
    DataLabel *scoreLabel,levelLabel;

    /** Metoda rysująca elementy ekranu końca gry
     */
    void draw(sf::RenderWindow &window);
public:
    /** Konstruktor, który tworzy odpowiednie napisy.
     */
    GameOver(sf::Font &f,int level,int score);

    /** Destruktor. Usuwa etykietę z ilością zebranych przez gracza punktów.
     */
    ~GameOver();

    /** Metoda wyświetlająca ekran końca gry.
     */
    void display(sf::RenderWindow &window);
};
#endif
