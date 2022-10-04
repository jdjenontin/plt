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

int Player::continentBonusTroop ()
{
    int ameriqueN(0), ameriqueS(0), europe(0), afrique(0), oceanie(0), asie(0);
    int numberBonusTroop(0);

    for(auto country : listCountry){
        if(country.getNumberCountry() < 9)
            ameriqueN += 1;
        else if (country.getNumberCountry() < 13)
            ameriqueS += 1;
        else if (country.getNumberCountry() < 19)
            afrique += 1;
        else if (country.getNumberCountry() < 26)
            europe += 1;
        else if (country.getNumberCountry() < 38)
            asie += 1;
        else oceanie;
    }

    // Ajout des troupes bonus
    if (ameriqueN == 9) numberBonusTroop += 5;
    if (ameriqueS == 4) numberBonusTroop += 2;
    if (afrique == 6) numberBonusTroop += 3;
    if (europe == 7) numberBonusTroop += 5;
    if (asie == 12) numberBonusTroop += 7;
    if (oceanie == 4) numberBonusTroop += 2;

    return numberBonusTroop;

}
}

