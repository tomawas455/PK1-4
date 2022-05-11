/** @file */
#ifndef LABELS
#define LABELS

#include <string>
#include <SFML/Graphics.hpp>

/** Podstawowa klasa reprezentująca napis na ekranie
 */
class Label:public sf::Drawable
{
protected:
    sf::Text label;
public:
    /** Konstruktor który tworzy podany napis zgodnie z argumentami.
     * @param t Tekst który napis ma wyświetlać.
     * @param font Czcionka tekstu.
     * @param pos Pozycja tekstu na ekranie.
     * @param posOrigin Ile razy względem lewego górnego rogu napisu ma być przesunięty środek napisu (dotyczy zarówno od boku jak i od góry).
     * @param size Rozmiar czcionki napisu.
     * @param color Kolor tekstu.
     */
    Label(std::string t,sf::Font &font,sf::Vector2i pos,float posOrigin=0,int size=15,sf::Color color=sf::Color::White);

    /** Metoda rysująca napis na podanym oknie, wymagana przez dziedziczenie po sf::Drawable
     * @param target Okno na którym ma być narysowany napis.
     * @param states Stany do dodania wobec rysowanego napisu.
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

/** Klasa pozwalająca dodać do statycznego napisu daną i jej aktualizowanie.
 */
class DataLabel:public Label
{
    std::string text;
    bool dataOnLeft;
    float positionOrigin;
    sf::Vector2i position;
public:
    /** Konstruktor tworzący podany napis.
     * @param t Tekst który napis ma wyświetlać.
     * @param font Czcionka tekstu.
     * @param pos Pozycja tekstu na ekranie.
     * @param posOrigin Ile razy względem lewego górnego rogu napisu ma być przesunięty środek napisu (dotyczy zarówno od boku jak i od góry).
     * @param size Rozmiar czcionki napisu.
     * @param color Kolor tekstu.
     * @param data Dodatkowa dana do dodania do statycznego tekstu.
     * @param dataLeft Parametr decydujący czy daną dodać po lewej (true) czy prawej (false) stronie statycznego tekstu.
     */
    DataLabel(std::string t,sf::Font &font,sf::Vector2i pos,float posOrigin=0,int size=15,sf::Color color=sf::Color::White,std::string data="",bool dataLeft=false);

    /** Metoda do aktualizacji zawartości napisu.
     * @param d Nowa wartość danej.
     */
    void updateData(std::string d);
};

/** Klasa klikalnego napisu
 */
class ClickableLabel:public Label
{
    sf::Color normalColor,hoverColor;
public:
    /** Konstruktor tworzący podany napis.
     * @param t Tekst który napis ma wyświetlać.
     * @param font Czcionka tekstu.
     * @param pos Pozycja tekstu na ekranie.
     * @param posOrigin Ile razy względem lewego górnego rogu napisu ma być przesunięty środek napisu (dotyczy zarówno od boku jak i od góry).
     * @param size Rozmiar czcionki napisu.
     * @param color Kolor tekstu.
     * @param hColor Kolor tekstu po najechaniu na niego myszką.
     */
    ClickableLabel(std::string t,sf::Font &font,sf::Vector2i pos,float posOrigin=false,int size=15,sf::Color color=sf::Color::White,sf::Color hColor=sf::Color::Green);

    /** Metoda zmieniająca kolor tekstu w zależności od pozycji myszki.
     * hoverColor jeśli myszka jest na napisie, normalColor jeśli nie.
     *
     * @param bounds Współrzędne myszki na ekranie.
     */
    void update(sf::Vector2i &bounds);

    /** Metoda zwracająca informację czy myszka w danym momencie znajduje się na napisie.
     * @return true jeśli myszka znajduje się na napisie, false w innym przypadku.
     */
    bool isHovered();
};
#endif
