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
    
}