/** @file */
#ifndef STATUSBAR
#define STATUSBAR

#include <SFML/Graphics.hpp>
#include "labels.h"

/** Klasa ta odpowiada za informacje na górze ekranu, jak np. pozostały czas czy poziom.
 */
class Statusbar:public sf::Drawable
{
private:
    DataLabel levelLabel,gemsLabel,timeLabel,scoreLabel;
    int level,gems,score;
    float time;
    sf::Vertex line[2];
public:
    /** Konstruktor tworzący pasek z początkowymi danymi.
     * @param f Czcionka do użycia w napisach.
     */
    Statusbar(sf::Font &f);

    /** Metoda rysująca napisy na podanym oknie, wymagana przez dziedziczenie po sf::Drawable
     * @param target Okno na którym ma być narysowany pasek z informacjami.
     * @param states Stany do dodania wobec rysowanych napisów.
     */
    void draw(sf::RenderTarget &target,sf::RenderStates states) const;

    /** Metoda zwiększająca poziom o jeden oraz edytująca napis zawierający informacje o poziomie.
     */
    void addLevel();

    /** Metoda dodająca kryształ oraz zmieniająca napis z informacją o ilości zebranych kryształów.
     */
    void addGem();

    /** Metoda resetująca poziom kryształów do zera, edytuje też napis z informacją o ilości zebranych kryształów.
     */
    void resetGems();

    /** Metoda resetująca czas do początkowej wartości, edytuje też napis z informacją o pozostałym czasie.
     */
    void resetTime();

    /** Metoda zwracająca obecny poziom.
     */
    int getLevel(){return level;}

    /** Metoda zwracająca obecny winik punktowy gracza.
     */
    int getScore(){return score;}

    /** Metoda aktualizująca ilość pozostałego czasu i zwracająca informację czy się skończył.
     * @param elapsed Ile czasu upłynęło od ostatniej aktualizacji.
     * @return true jeśli ilość pozostałego czasu jest większa niż zero. False w innym przypadku.
     */
    bool isTime(float elapsed);
};

#endif
