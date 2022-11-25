#include "Card.h"

namespace state{

Card::Card () {

}

Card::Card(std::string nameCountry, TypeCard typeCard){
    this->country = nameCountry;
    this->typeCard = typeCard;
}

Card::~Card () {

}

std::string Card::getNameCountry(){
    return country;
}

}