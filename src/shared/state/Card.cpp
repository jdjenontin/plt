#include "Card.h"

namespace state{

Card::Card () {

}

Card::Card(std::string name, TypeCard typeCard){
    this->country = name;
    this->typeCard = typeCard;
}

Card::~Card () {

}

std::string Card::getName(){
    return country;
}

}