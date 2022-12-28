#include "Place.h"

namespace engine {

Place::Place(){

}

Place::~Place(){

}

void Place::setCountry(const std::shared_ptr<state::Country>& country){
    this->country = country;
}

void Place::execute (){
    if(player->existCountry(*country)){
        country->addTroop(1);
        bonus_troop--;
    }
}

}