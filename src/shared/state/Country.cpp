#include "Country.h"

namespace state{

Country::Country () {

}

Country::~Country () {

}

Country::Country (std::string name , int number) {
    nameCountry = name;
    numberCountry = number;
}

std::string Country::getNameCountry () {
    return nameCountry;
}

int Country::getNumberCountry () {
    return numberCountry;
}

int Country::getNumberTroop () {
    return numberTroop;
}

void Country::setNumberTroop (int numTroop) {
    numberTroop = numTroop;
}

void Country::addNumberTroop (int numTroop) {
    numberTroop += numTroop;
}

void Country::reduceNumberTroop (int numTroop) {
    numberTroop -= numTroop;
}

}