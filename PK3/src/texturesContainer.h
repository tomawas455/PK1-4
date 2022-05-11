/** @file */
#ifndef TEXTURES_CONTAINER
#define TEXTURES_CONTAINER

#include <SFML/Graphics.hpp>

/** Klasa przechowyjąca tekstury elementów gry.
 */
class TexturesContainer
{
private:
    sf::Texture empty,ground,boulder,lava,player,gem,exit;
public:
    /** Konstruktor wczytujący wszystkie tekstury.
     */
    TexturesContainer();

    /** Metoda zwracająca referencję do pustej tekstury.
     * @return Referencja do tekstury pustego elementu.
     */
    sf::Texture& getEmpty(){return empty;}

    /** Metoda zwracająca referencję do tekstury ziemi.
     * @return Referencja do tekstury ziemi.
     */
    sf::Texture& getGround(){return ground;}

    /** Metoda zwracająca referencję do tekstury kamienia.
     * @return Referencja do tekstury kamienia.
     */
    sf::Texture& getBoulder(){return boulder;}

    /** Metoda zwracająca referencję do tekstury lawy.
     * @return Referencja do tekstury lawy.
     */
    sf::Texture& getLava(){return lava;}

    /** Metoda zwracająca referencję do tekstury gracza.
     * @return Referencja do tekstury gracza.
     */
    sf::Texture& getPlayer(){return player;}

    /** Metoda zwracająca referencję do tekstury kryształu.
     * @return Referencja do tekstury kryształu.
     */
    sf::Texture& getGem(){return gem;}

    /** Metoda zwracająca referencję do tekstury wyjścia.
     * @return Referencja do tekstury wyjścia.
     */
    sf::Texture& getExit(){return exit;}
};

#endif
