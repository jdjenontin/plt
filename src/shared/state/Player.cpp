#include "Player.h"
#include <iostream>

using namespace std;

namespace state{

Player::Player () {
    ownTroop = 35;
}
//Tacitement le nombre de troup est 35 pour les 3 joueurs 

Player::~Player () {

}

Player::Player (std::vector<Country> lcountry, std::vector<Card> lcard, int troop) {
    listCountry = lcountry;
    listCard = lcard;
    ownTroop = troop;
}

void Player::place (Country country, int numberTroop) {
    cout << "Please place your troop" << endl;
    country.numberTroup += numberTroop;
}

void Player::attack (Country country1, Country country2) {
    Calculation calcul;
    cout << "Please attack somebody" << endl;

}

void Player::reinforce (Country country1, Country country2, int numberTroop) {
    cout << "Please move your troop" << endl;
}

void Player::addCountry (Country country) {
    listCountry.push_back(country);
}

void Player::deleteCountry (Country country) {

}

void Player::addCard (Card card) {

}

void Player::deleteCard (Card card) {

}

int Player::getownTroop () {
    return ownTroop;
}

std::vector<Country> Player::getListCountry () {
    return listCountry;
}

}