/** @file */
#ifndef PLAYER_
#define PLAYER_

#include <SFML/Graphics.hpp>
#include "tiles.h"

/** Klasa reprezentująca gracza na mapie.
 */
class Player:public GameTile
{
private:
    /** Metoda przesuwająca gracza jeśli jest to możliwe.
     * Metoda sprawdza czy gracz może stanąć na kafelku na który chce iść.
     * Jeśli może to przesuwa jego grafikę na tę pozycję.
     *
     * @param tiles Plansza gry.
     * @param newTileX Współrzędna x-owa kafelka na który chce gracz iść.
     * @param newTileY Współrzędna y-owa kafelka na który chce gracz iść.
     * @param moveX O ile pikseli trzeba przesunąć grafikę gracza poziomo w przypadku kiedy może on stanąć na kafelku z nowej pozycji.
     * @param moveY O ile pikseli trzeba przesunąć grafikę gracza pionowo w przypadku kiedy może on stanąć na kafelku z nowej pozycji.
     */
    void move(CollidableTile ***tiles,int newTileX,int newTileY,int moveX,int moveY);

    /** Funkcja decydująca czy gracz może stanąć na podanym kafelku.
     * Gracz może stanąć tylko na kafelku pustym lub zawierającym ziemię.
     *
     * @param t Kafelek do sprawdzenia.
     */
    bool canStandOn(CollidableTile *t);
public:
    /** Konstruktor tworzący gracza
     * @param t Tekstura gracza.
     * @param pos Pozycja startowa gracza.
     */
    Player(sf::Texture &t,sf::Vector2i pos):GameTile(t,pos,GameTile::tileTypes::PLAYER){}

    /** Metoda ustawiająca gracza na podanej pozycji.
     * @param newPosition Pozycja na którą ma trafić gracz.
     */
    void setPosition(sf::Vector2i newPosition);

    /** Metoda odpowiedzialna za przemieszcza nie gracza po planszy.
     * @param tiles Plansza gry.
     * @param event Zdarzenie zgłoszone przez ekran gry (np. naciśnięcie przycisku na klawiaturze).
     * @return true jeśli gracz spróbował się poruszyć, false w innym przypadku.
     */
    bool move(CollidableTile ***tiles,sf::Event &event);

    /** Metoda zwracająca współrzędne kafelka na którym znajduje się gracz.
     * Jako, że gracz nie przechowuje tej informacji to metoda ta liczy to z współrzędnych gracza na oknie gry.
     *
     * @return Współrzędne kafelka z graczem na planszy.
     */
    sf::Vector2i getTile();
};

#endif
