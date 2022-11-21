#include "Card.h"

namespace render{

Card::Card(int x, int y) {
    sf::Vector2f size;

    size.x = 150;
    size.y = 200;

    position.x = x;
    position.y = y;

    rectangle.setSize(size);
    rectangle.setPosition(x, y);
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(3);
}

Card::~Card() {

}

const sf::RectangleShape& Card::getRectangle() const{
    return rectangle;
}

}