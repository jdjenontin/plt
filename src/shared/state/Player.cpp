#include "Player.h"
#include <iostream>
#include <string>
#include <string.h>

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

void Player::place (Country &country, int numberTroop) {
    cout << "place!" << endl;

    country.numberTroop += numberTroop;
}

int Player::attack (Country &attacker, Country &defender) {
    char choose[50];
    int n_troop;

    Calculation calcul;
    cout << "attack!" << endl;
    calcul.compute(attacker, defender);

    std::cout << "do you want attack? If yes, type true or type any letter for return :\n";
    cin >> choose; 

    std::cout << choose << std::endl;
    //dans le if il faut ajouter une operation 
    if(strcmp(choose, "true") == 0){
        if(calcul.attack(attacker, defender) == 0) {
            addCountry(defender);
            cout << "choose the quantity of troop that you want put in new country :";
            cin >> n_troop;
            attacker.reduceNumberTroop(n_troop);
            place(defender, n_troop);
        }
        else {
        }
        return 0;
    }
    else{
        std::cout << "its not available now" << std::endl;
        return 1;
    }
    return 1;
}

void Player::reinforce (Country &country1, Country &country2, int numberTroop) {
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