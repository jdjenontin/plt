#include "Place.h"
#include <iostream>

using namespace std;

namespace engine {

Place::Place(){

}

Place::~Place(){

}

void Place::setCountry(const std::shared_ptr<state::Country>& country){
    this->country = country;
}

void Place::execute (){
    if(player->existCountry(*country)){;
        country->addTroop(1);
        bonus_troop--;
        std::cout << bonus_troop << std::endl;
    }
}

}