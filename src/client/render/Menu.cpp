#include "Menu.h"

#include <iostream>

namespace render {

sf::Texture button;

Menu::Menu (int x, int y) {
    position.x = x;
    position.y = y;
}

Menu::~Menu () {

}

Menu::Menu (int x, int y, std::string name) {
    sf::Vector2f size;

    size.x = 200;
    size.y = 50;
    button.loadFromFile("res/m_button.png");

    this->name = name;
    position.x = x;
    position.y = y;
    float t = (float)name.size() / 2;

    this->message = new Message(x - t*10 - 8, y - 14, name);
    this->message->setColor(sf::Color::White);
    rectangle.setSize(size);
    rectangle.setPosition(x - 100, y - 25);
    rectangle.setTexture(&button);
}

Menu::Menu (int x, int y, int length, int height, sf::Texture* texture, std::string name){
    sf::Vector2f size(length, height);
    position.x = x;
    position.y = y;

    this->name = name;
    float t = (float)name.size() / 2;
    this->message = new Message(x - t*10 - 8, y - 14, name);
    this->message->setColor(sf::Color::White);
    rectangle.setSize(size);
    rectangle.setPosition(x - length/2, y - height/2);
    rectangle.setTexture(texture);
}

void Menu::addMessage (int x, int y, int size, std::string message, sf::Color color){
    this->message = new Message(x, y, message);
    this->message->setColor(color);
    this->message->setSize(size);
    this->name = message;
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