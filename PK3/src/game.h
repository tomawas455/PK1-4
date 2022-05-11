/** @file */
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <random>
#include "statusbar.h"
#include "tiles.h"
#include "texturesContainer.h"
#include "player.h"
#include "constants.h"

/** Klasa reprezentująca trwającą rozgrywkę, zarządzająca aktualizacjami itp.
 */
class Game
{
private:
    Statusbar bar;
    CollidableTile ***tiles;
    Player *player;
    TexturesContainer textures;
    sf::Font &font;

    /** stan rozgrywki, tj. czy ona trwa, skończyła się, czy gracz zamknął okno.
     */
    enum states{PLAY,OVER,EXIT};
    states state;

    /** Metoda tworząca mapę gry.
     * Najpierw zapełniamy ją elementami ziemi.
     * Następnie zastępujemy część z nich zamieniamy na inne elementy (kamień, lava itp.)
     */
    void createTiles();

    /** Metoda tworzy mapę i zapełnia ją elementami ziemi.
     * Tworzona jest dynamicznie dwuwymiarowa tablica wskaźników tiles jeśli jeszcze nie istnieje.
     * Następnie w każdej komórce tworzony jest element ziemi, usuwając wcześniej zajmujący tę komórkę element jeśli konieczne.
     */
    void resetMap();

    /** Metoda dodająca na mapie kamienie.
     * @param amount Ile kamieni ma się na mapie pojawić.
     * @param randomEngine Silnik generujący liczby losowe.
     */
    void generateBoulders(int amount,std::default_random_engine &randomEngine);

    /** Metoda znajdująca miejsce dla elementu do dodania na mapę.
     * Metoda ta wybiera losowe współrzędne i sprawdza czy kafelek na tej pozycji jest typu ziemia.
     * @param x Zmienna do której trafi współrzędna x.
     * @param y Zmienna do której trafi współrzędna y.
     * @param randomEngine Silnik generujący liczby losowe.
     */
    void getCoords(int &x,int &y,std::default_random_engine &randomEngine);

    /** Metoda dodająca na mapie lawę.
     * @param amount Ile kafelków z lawą ma się na mapie pojawić.
     * @param randomEngine Silnik generujący liczby losowe.
     */
    void generateLava(int amount,std::default_random_engine &randomEngine);

    /** Metoda dodająca na mapie kryształy do zebrania.
     * @param amount Ile kryształów ma się na mapie pojawić.
     * @param randomEngine Silnik generujący liczby losowe.
     */
    void generateGems(int amount,std::default_random_engine &randomEngine);

    /** Metoda dodająca na mapie wyjście pozwalające wejść na kolejny poziom.
     * @param randomEngine Silnik generujący liczby losowe.
     */
    void generateExit(std::default_random_engine &randomEngine);

    /** Metoda dodająca na mapie gracza w lewym górnym rogu.
     * Przenosi gracza, zamiast go usuwać i dodawać na odpowiedniej pozycji.
     */
    void generatePlayer();

    /** Metoda wywołuje metodę update na każdym elemencie mapy.
     * Dzięki temu kamienie mogą się stoczyć, a lawa popłynąć.
     */
    void updateElements();

    /** Metoda sprawdzająca reakcję na kolizję elementu na którym stoi gracz z graczem.
     * Dzięki temu można zebrać kryształy, spadający kamień gracza zabije itp.
     */
    void collisionEffect();

    /** Metoda rysująca pasek stanu u góry, mapę oraz gracza
     */
    void draw(sf::RenderWindow &window);
public:
    /** Konstruktor tworzący pasek u góry, gracza i ustawiający stan gry na PLAY.
     */
    Game(sf::Font &f);

    /** destruktor usuwa wszystkie kafelki, oba wymiary tablicy która je trzymała oraz gracza.
     */
    ~Game();

    /** Metoda wyświetlająca rozgrywkę, aktualizuje ją itp. poprzez wywoływanie odpowiednich metod tej klasy.
     */
    void display(sf::RenderWindow &window);
};

#endif
