#include "Card.h"

namespace state{

Card::Card () {

}

Card::Card(std::string nameCountry, TypeCard typeCard){
    country = nameCountry;
    typeCard = typeCard;
}

Card::~Card () {

}

std::string Card::getNameCountry(){
    return country;
}

}