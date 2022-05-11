#include "labels.h"

Label::Label(
    std::string t,
    sf::Font &font,
    sf::Vector2i pos,
    float posOrigin,
    int size,
    sf::Color color)
{
    label=sf::Text(t,font,size);
    label.setFillColor(color);
    sf::FloatRect localBounds=label.getLocalBounds();
    label.setPosition(sf::Vector2f(pos.x-posOrigin*localBounds.width,pos.y-posOrigin*localBounds.height));
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(label,states);
}

DataLabel::DataLabel(
    std::string t,
    sf::Font &font,
    sf::Vector2i pos,
    float posOrigin,
    int size,
    sf::Color color,
    std::string d,
    bool dataLeft
):
    Label(t, font, pos, posOrigin, size, color),
    text(t), dataOnLeft(dataLeft), positionOrigin(posOrigin)
{
    label.setString((dataOnLeft?d+text:text+d));
    position=pos;
    if(d.length())
    {
        sf::FloatRect localBounds=label.getLocalBounds();
        label.setPosition(sf::Vector2f(
            pos.x-posOrigin*localBounds.width,
            pos.y-posOrigin*localBounds.height
        ));
    }
}

void DataLabel::updateData(std::string d)
{
    label.setString((dataOnLeft?d+text:text+d));
    sf::FloatRect localBounds=label.getLocalBounds();
    sf::Vector2f pos(
        position.x-positionOrigin*localBounds.width,
        position.y-positionOrigin*localBounds.height
    );
    label.setPosition(pos);
}

ClickableLabel::ClickableLabel(
    std::string t,
    sf::Font &font,
    sf::Vector2i pos,
    float posOrigin,
    int size,
    sf::Color color,
    sf::Color hColor
): Label(t,font,pos,posOrigin,size,color), normalColor(color), hoverColor(hColor)
{}

void ClickableLabel::update(sf::Vector2i &bounds)
{
    if(label.getGlobalBounds().contains(bounds.x,bounds.y))
        label.setFillColor(hoverColor);
    else
        label.setFillColor(normalColor);
}

bool ClickableLabel::isHovered()
{
    return label.getFillColor() == hoverColor;
}
