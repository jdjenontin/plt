#include "Place.h"

namespace engine {

Place::Place(){

}

Place::~Place(){

}

void Place::setcountry (state::Country* country){
    this->country = country;
}

int Place::execute (){
    if(player->existCountry(*country)){
        country->addNumberTroop(1);
        bonus_troop--;
        return 1;
    }
    
    return 0;
}

}