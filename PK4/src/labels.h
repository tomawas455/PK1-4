#ifndef LABELS
#define LABELS

#include <string>
#include <SFML/Graphics.hpp>

// Podstawowa klasa reprezentująca napis na ekranie
class Label: public sf::Drawable
{
protected:
    sf::Text label;
public:
    // Konstruktor który tworzy podany napis zgodnie z argumentami.
    Label(
        std::string t,
        sf::Font &font,
        sf::Vector2i pos,
        float posOrigin=0,
        int size=15,
        sf::Color color=sf::Color::White
    );

    // Metoda rysująca napis na podanym oknie, wymagana przez dziedziczenie po sf::Drawable
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

// Klasa pozwalająca dodać do statycznego napisu daną i jej aktualizowanie.
class DataLabel: public Label
{
    std::string text;
    bool dataOnLeft;
    float positionOrigin;
    sf::Vector2i position;
public:
    // Konstruktor tworzący podany napis.
    DataLabel(
        std::string t,
        sf::Font &font,
        sf::Vector2i pos,
        float posOrigin = 0,
        int size = 15,
        sf::Color color=sf::Color::White,
        std::string data = "",
        bool dataLeft = false
    );

    // Metoda do aktualizacji zawartości napisu.
    void updateData(std::string d);
};

// Klasa klikalnego napisu
class ClickableLabel: public Label
{
    sf::Color normalColor,hoverColor;
public:
    // Konstruktor tworzący podany napis.
    ClickableLabel(
        std::string t,
        sf::Font &font,
        sf::Vector2i pos,
        float posOrigin=false,
        int size=15,
        sf::Color color=sf::Color::White,
        sf::Color hColor=sf::Color::Cyan
    );

    // Metoda zmieniająca kolor tekstu w zależności od pozycji myszki.
    void update(sf::Vector2i &bounds);

    // Metoda zwracająca informację czy myszka w danym momencie znajduje się na napisie.
    bool isHovered();
};
#endif
