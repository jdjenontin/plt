#include "Card.h"

namespace render{

Card::Card(int x, int y, std::string name, std::string country) {
    sf::Vector2f size;

    sf::Texture t;
    t.loadFromFile("res/risk-pions.png");
    pion.setTexture(t);

    size.x = 200;
    size.y = 300;

    position.x = x;
    position.y = y;

    rectangle.setSize(size);
    rectangle.setPosition(x, y);
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(3);

    if(name == "Infantry"){
        pion.setTextureRect(sf::IntRect(100, 50, 100, 150));
        pion.setPosition(x + 50, y + 70);
    }
    else if(name == "Cavalry"){
        pion.setTextureRect(sf::IntRect(300, 50, 100, 150));
        pion.setPosition(x + 50, y + 70);
    }
    else if(name == "Artillery"){
        pion.setTextureRect(sf::IntRect(500, 50, 100, 150));
        pion.setPosition(x + 50, y + 70);
    }

    this->name = new Message(x + 50, y + 10, name);
    this->country = new Message(x + 50, y + 250, country);

    this->country->cutMessage();
}

Card::~Card() {

}

const sf::RectangleShape& Card::getRectangle() const{
    return rectangle;
}

const Message* Card::getCountry (){
    return country;
}

const Message* Card::getName (){
    return name;
}

const sf::Sprite& Card::getPion() const{
    return pion;
}

}