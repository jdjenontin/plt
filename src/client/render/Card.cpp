#include "Card.h"

namespace render{

sf::Texture t;

Card::Card(int x, int y, std::string name, std::string country) {
    sf::Vector2f size;

    t.loadFromFile("res/cartes-risk.png");
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
        pion.setTextureRect(sf::IntRect(620, 110, 80, 90));
        pion.setPosition(x + 60, y + 100);
    }
    else if(name == "Cavalry"){
        pion.setTextureRect(sf::IntRect(620, 10, 80, 100));
        pion.setPosition(x + 60, y + 100);
    }
    else if(name == "Artillery"){
        pion.setTextureRect(sf::IntRect(620, 200, 80, 70));
        pion.setPosition(x + 60, y + 110);
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