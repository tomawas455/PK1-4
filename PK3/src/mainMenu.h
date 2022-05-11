/** @file */
#ifndef MAIN_MENU
#define MAIN_MENU
#define MENU_OPTIONS 2

#include <SFML/Graphics.hpp>
#include "labels.h"

/** Klasa reprezuntująca menu główne gry.
 */
class MainMenu
{
    Label *title;
    ClickableLabel *options[MENU_OPTIONS];

    /** Metoda rysująca w oknie napisy menu głównego.
     * @param window Okno na którym mają zostać narysowane elementy menu.
     */
    void draw(sf::RenderWindow &window);
public:
    /** Konstruktor tworzący odpowiednie napisy do menu głównego.
     * @param font Czcionka napisów.
     */
    MainMenu(sf::Font &font);

    /** Destruktor usuwające napisy menu głównego.
     */
    ~MainMenu();

    /** Enum informujący którą opcję gracz wybrał w menu głównym.
    */
    enum choice{START=0,EXIT};

    /** Metoda wyświetlająca menu główne
     * @param window Okno na którym należy wyświetlić menu główne
     * @return Wybrana przez gracza opcja.
     */
    choice display(sf::RenderWindow &window);
};
#endif
