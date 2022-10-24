#include "Player.h"
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

namespace state{

Player::Player () {
    ownTroop = 35;
    status = PLAYING;
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

    country.addNumberTroop(numberTroop);
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
    int i = 0;
    while(listCountry[i].getNameCountry() != country.getNameCountry()){
        i++;
    }
    listCountry.erase(listCountry.begin() + i);
}

void Player::addCard (Card card) {
    listCard.push_back(card);
}

void Player::deleteCard (Card card) {
    int i = 0;
    while(listCard[i].getNameCountry() != card.getNameCountry()){
        i++;
    }
    listCard.erase(listCard.begin() + i);
}

int Player::getownTroop () {
    return ownTroop;
}

const std::vector<Country>& Player::getListCountry () const{
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
        else 
            oceanie +=1;
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

