#include "Menu.h"

namespace render {

Menu::Menu (int x, int y) {
    position.x = x;
    position.y = y;
}

Menu::~Menu () {

}

Menu::Menu (int x, int y, std::string name) {
    sf::Vector2f size;

    size.x = 100;
    size.y = 50;

    this->name = name;
    position.x = x;
    position.y = y;

    message = new Message(x, y, name);
    rectangle.setSize(size);
    rectangle.setPosition(x - 25, y - 10);
    rectangle.setFillColor(sf::Color::Green);
}

const sf::RectangleShape& Menu::getRectangle() const{
    return rectangle;
}

const Message* Menu::getMessage() {
    return message;
}

std::string Menu::getName() {
    return name;
}

sf::Vector2i Menu::getPostion () {
    return position;
}

}