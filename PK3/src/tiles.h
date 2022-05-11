/** @file */
#ifndef TILES
#define TILES

#include <SFML/Graphics.hpp>

#include "constants.h"
#include "texturesContainer.h"

/** Klasa kafelka z gry
 */
class GameTile:public sf::Drawable
{
public:
    /** Typy kafelków w grze.
     * Na tej podstawie można stwierdzić czy np. kamień może się stoczyć w danym kierunku, albo gdzie gracz może pójść.
     */
    enum tileTypes{EMPTY=0,GROUND,PLAYER,BOULDER,LAVA,SPECIAL};

    /** Konstruktor ustawiający grafikę i typ kafelka.
     * @param t Tekstura danego elementu.
     * @param po Pozycja na ekranie.
     * @param tt Typ tworzonego elementu.
     */
    GameTile(sf::Texture &t,sf::Vector2i pos,GameTile::tileTypes tt);

    /** Metoda rysująca napisy w podanym oknie, wymagana przez dziedziczenie po sf::Drawable
     * @param target Okno na którym ma być narysowany dany element.
     * @param states Stany do dodania wobec rysowanego elementu.
     */
    void draw(sf::RenderTarget &target,sf::RenderStates states) const;

    /** Metoda zwracająca typ kafelka.
     * @return Zwraca wartość tileType.
     */
    tileTypes getType(){return tileType;}
protected:
    sf::Sprite sprite;
    GameTile::tileTypes tileType;
};

/** Klasa dla elementów z którymi gracz może wejść w kolizję.
 */
class CollidableTile:public GameTile
{
public:
    /** Możliwe wyniki kolizji danego elementu z graczem.
     */
    enum collisionEffects{NOTHING=0,DESTROY_ELEMENT,END_GAME,ADD_POINTS,NEXT_LEVEL};

    /** Konstruktor tworzący kolizyjny kafelek.
     * @param t Tekstura danego elementu.
     * @param pos Pozycja w oknie.
     * @param tt Typ tworzonego elementu.
     * @param cEff Efekt kolizji danego elementu z graczem.
     */
    CollidableTile(sf::Texture &t,sf::Vector2i pos,GameTile::tileTypes tt,collisionEffects cEff=NOTHING):GameTile(t,pos,tt),colEffect(cEff){}

    /** Metoda zwracająca wynik kolizji tego elementu z graczem.
     * @return wartość zmiennej colEffect.
     */
    collisionEffects getColEffect(){return colEffect;}

    /** Metoda która ma implementować sposób aktualizacji danego elementu, np. staczanie się kamienia.
     * @param tiles Plansza gry.
     * @param tc Kontener ze wszystkimi teksturami w grze.
     * @param tileX x-owa współrzędna kafelka na którym dany element się znajduje.
     * @param tileY y-owa współrzędna kafelka na którym dany element się znajduje.
     */
    virtual void update(CollidableTile ***tiles,TexturesContainer &tc,int tileX,int tileY)=0;
protected:
    CollidableTile::collisionEffects colEffect;
};

class Empty:public CollidableTile
{
public:
    /** Konstruktor tworzący pusty element.
     * @param t Tekstura pustego elementu.
     * @param pos Pozycja w oknie.
     */
    Empty(sf::Texture &t,sf::Vector2i pos):CollidableTile(t,pos,GameTile::tileTypes::EMPTY){}

    /** Metoda update konieczna z powodu dziedziczenia po CollidableTile.
     * Nic nie robi.
     *
     * @param tiles Plansza gry.
     * @param tc Kontener ze wszystkimi teksturami w grze.
     * @param tileX x-owa współrzędna kafelka na którym dany pusty element się znajduje.
     * @param tileY y-owa współrzędna kafelka na którym dany pusty element się znajduje.
     */
    void update(CollidableTile ***tiles,TexturesContainer &tc,int tileX,int tileY){}
};

class Ground:public CollidableTile
{
public:
    /** Konstruktor tworzący ziemi.
     * @param t Tekstura ziemi.
     * @param pos Pozycja w oknie.
     */
    Ground(sf::Texture &t,sf::Vector2i pos):CollidableTile(t,pos,GameTile::tileTypes::GROUND,CollidableTile::collisionEffects::DESTROY_ELEMENT){}

    /** Metoda update konieczna z powodu dziedziczenia po CollidableTile.
     * Nic nie robi.
     *
     * @param tiles Plansza gry.
     * @param tc Kontener ze wszystkimi teksturami w grze.
     * @param tileX x-owa współrzędna kafelka na którym dany element ziemi się znajduje.
     * @param tileY y-owa współrzędna kafelka na którym dany element ziemi się znajduje.
     */
    void update(CollidableTile ***tiles,TexturesContainer &tc,int tileX,int tileY){}
};

class Boulder:public CollidableTile
{
public:
    /** Konstruktor tworzący kamień.
     * @param t Tekstura kamienia.
     * @param pos Pozycja w oknie.
     */
    Boulder(sf::Texture &t,sf::Vector2i pos):CollidableTile(t,pos,GameTile::tileTypes::BOULDER,CollidableTile::collisionEffects::END_GAME){}
    /** Decyduje czy kamień może spaść w lewo/prawo/dół i wykonuje tę akcję jeśli tak.
     * @param tiles Plansza gry.
     * @param tc Kontener ze wszystkimi teksturami w grze.
     * @param tileX x-owa współrzędna kafelka na którym dany kamień się znajduje.
     * @param tileY y-owa współrzędna kafelka na którym dany kamień się znajduje.
     */
    void update(CollidableTile ***tiles,TexturesContainer &tc,int tileX,int tileY);
private:
    /** Zwraca informację czy dany kamień znajduje się na elemencie z którego może spaść.
     * Kamień może spaść tylko jeśli znajduje się na innym kamieniu, nad pustym miejscem oraz nad lawą.
     *
     * @param tt typ elementu pod danym kamieniem.
     */
    bool onFallableTile(GameTile::tileTypes &tt);

    /** Powoduje upadek kamienia w dół i zwraca informację czy to się udało.
     * @param tiles Plansza gry.
     * @param emptyTexture Tekstura pustego elementu.
     * @param tileX x-owa współrzędna kafelka na którym dany kamień się znajduje.
     * @param tileY y-owa współrzędna kafelka na którym dany kamień się znajduje.
     * @param bottomTileType Typ elementu pod danym kamieniem.
     * @return true jeśli kamień spadnie w dół, false jeśli nie.
     */
    bool fellDown(CollidableTile ***tiles,sf::Texture &emptyTexture,int tileX,int tileY,GameTile::tileTypes &bottomTileType);

    /** Przesuwaja kamień na nową pozycję.
     * @param tiles Plansza gry.
     * @param destinationX x-owa współrzędna kafelka docelowego dla danego kamienia.
     * @param destinationY y-owa współrzędna kafelka docelowego dla danego kamienia.
     * @param posX Aktualna x-owa współrzędna kafelka dla danego kamienia.
     * @param posY Aktualna y-owa współrzędna kafelka dla danego kamienia.
     */
    void move(CollidableTile ***tiles,int destinationX,int destinationY,int &posX,int &posY,sf::Texture &emptyTexture);

    /** Ustawia kamień na nowej pozycji w oknie.
     * @param x x-owa współrzędna nowej pozycji.
     * @param y y-owa współrzędna nowej pozycji.
     */
    void setPosition(int x,int y);

    /** Powoduje upadek kamienia w bok i zwraca informację czy to się udało.
     * @param tiles Plansza gry.
     * @param emptyTexture Tekstura pustego elementu.
     * @param tileX x-owa współrzędna kafelka na którym dany kamień się znajduje.
     * @param tileY y-owa współrzędna kafelka na którym dany kamień się znajduje.
     * @param side Która strona updaku kamienia jest rozważana, powinno mieć wartość -1 lub 1.
     * @param xLimit Granica sprawdzania współrzędnych x-owych dla danego wywołania. Czyli jeśli xLimit < lub > od tileX to napewno zwracamy false.
     * @return true jeśli kamień spadnie w bok, false jeśli nie.
     */
    bool fellSide(CollidableTile ***tiles,sf::Texture &emptyTexture,int tileX,int tileY,int side,int xLimit);

    /** Zwraca informację czy kamień może spaść na dany typ elementu.
     * @param tt typ elementu do sprawdzenia.
     * @return true jeśli kamień może spaść na dany typ elementu, false jeśli nie.
     */
    bool canFall(CollidableTile::tileTypes &tt);
};

class Lava:public CollidableTile
{
public:
    /** Konstruktor tworzący lawę.
     * @param t Tekstura lawy.
     * @param pos Pozycja w oknie.
     * @param isN parametr określający czy dany element lawy jest nowy, tj czy najeży pominąć pierwsze wywołanie metody update.
     */
    Lava(sf::Texture &t,sf::Vector2i pos,bool isN=false):CollidableTile(t,pos,GameTile::tileTypes::LAVA,CollidableTile::collisionEffects::END_GAME),isNew(isN){}

    /** Decyduje czy lawa rozlać się w lewo/prawo/dół i wykonuje tę akcję jeśli tak.
     * @param tiles Plansza gry.
     * @param tc Kontener ze wszystkimi teksturami w grze.
     * @param tileX x-owa współrzędna kafelka na którym dany element lawy się znajduje.
     * @param tileY y-owa współrzędna kafelka na którym dany element lawy się znajduje.
     */
    void update(CollidableTile ***tiles,TexturesContainer &tc,int tileX,int tileY);
private:
    /** Próba rozlania lawy na podaną pozycję x/y.
     * @param tiles Plansza gry.
     * @param x x-owa współrzędna kafelka na który chcemy rozlać lawę.
     * @param y y-owa współrzędna kafelka na który chcemy rozlać lawę.
     * @param lavaTexture Tekstura lawy.
     * @param isN parametr określający wartość pola isNew w nowotworzonym elemencie lawy dla danego wywołania tej metody.
     */
    void trySpilling(CollidableTile ***tiles,int x,int y,sf::Texture &lavaTexture,bool isN);

    /** Sprawdzenie czy lawa może się rozlać na dany kafelek.
     * @param tt Typ kafelka który sprawdzamy.
     * @return true jeśli lawa może się rozlać na podany typ, false jeśli nie.
     */
    bool canSpill(GameTile::tileTypes tt);

    /** Rozlanie lawy na daną pozycję x/y.
     * @param tiles Plansza gry.
     * @param x x-owa współrzędna kafelka na który chcemy rozlać lawę.
     * @param y y-owa współrzędna kafelka na który chcemy rozlać lawę.
     * @param lavaTexture Tekstura lawy.
     * @param isN parametr określający wartość pola isNew w nowotworzonym elemencie lawy dla danego wywołania tej metody.
     */
    void spill(CollidableTile ***tiles,int x,int y,sf::Texture &lavaTexture,bool isN);
    bool isNew;
};

class Gem:public CollidableTile
{
public:
    /** Konstruktor tworzący kryształ.
     * @param t Tekstura kryształu.
     * @param pos Pozycja w oknie.
     */
    Gem(sf::Texture &t,sf::Vector2i pos):CollidableTile(t,pos,GameTile::tileTypes::SPECIAL,CollidableTile::collisionEffects::ADD_POINTS){}

    /** Metoda update konieczna z powodu dziedziczenia po CollidableTile.
     * Nic nie robi.
     *
     * @param tiles Plansza gry.
     * @param tc Kontener ze wszystkimi teksturami w grze.
     * @param tileX x-owa współrzędna kafelka na którym ten element się znajduje.
     * @param tileY y-owa współrzędna kafelka na którym ten element się znajduje.
     */
    void update(CollidableTile ***tiles,TexturesContainer &tc,int tileX,int tileY){}
};

class Exit:public CollidableTile
{
public:
    /** Konstruktor tworzący wyjście.
     * @param t Tekstura wyjścia.
     * @param pos Pozycja w oknie.
     */
    Exit(sf::Texture &t,sf::Vector2i pos):CollidableTile(t,pos,GameTile::tileTypes::SPECIAL,CollidableTile::collisionEffects::NEXT_LEVEL){}

    /** Metoda update konieczna z powodu dziedziczenia po CollidableTile.
     * Nic nie robi.
     *
     * @param tiles Plansza gry.
     * @param tc Kontener ze wszystkimi teksturami w grze.
     * @param tileX x-owa współrzędna kafelka na którym ten element się znajduje.
     * @param tileY y-owa współrzędna kafelka na którym ten element się znajduje.
     */
    void update(CollidableTile ***tiles,TexturesContainer &tc,int tileX,int tileY){}
};
#endif
