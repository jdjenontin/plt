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

}