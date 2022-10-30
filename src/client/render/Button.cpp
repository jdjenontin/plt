#include "Button.h"

namespace render{

Button::Button(){

}

Button::~Button(){

}

Button::Button(int rayon){
    circle.setRadius(rayon);
}

Button::Button(int x, int y, int rayon){
    circle.setPosition(x, y);
    circle.setRadius(rayon);
}

Button::Button (unsigned int x, unsigned int y, int rayon, sf::Color color, sf::Texture* texture){
    circle.setPosition(x, y);
    circle.setRadius(rayon);
    circle.setTexture(texture); // texture is a sf::Texture
    circle.setTextureRect(sf::IntRect(2, 2, 21, 20));
    circle.setFillColor(color);

}
    
}