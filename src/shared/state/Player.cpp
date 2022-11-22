#include "Player.h"
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

namespace state{

Player::Player () {
    status = PLAYING;
}
//Tacitement le nombre de troup est 35 pour les 3 joueurs 

Player::Player (int m_order) {
    status = PLAYING;
    order = m_order;
}

Player::~Player () {

}

void Player::addCountry (Country* country) {
    listCountry.push_back(country);
}

void Player::deleteCountry (Country* country) {
    int i = 0;
    while(listCountry[i] -> getNameCountry() != country -> getNameCountry()){
        i++;
    }
    listCountry.erase(listCountry.begin() + i);
}

void Player::addCard (Card* card) {
    listCard.push_back(card);
}

void Player::deleteCard (Card* card) {
    int i = 0;
    while(listCard[i]->getNameCountry() != card->getNameCountry()){
        i++;
    }
    listCard.erase(listCard.begin() + i);
}

void Player::setColor(const sf::Color& m_color){
    color = m_color;
}

const sf::Color& Player::getColor() const{
    return color;
}

int Player::getownTroop () {
    return ownTroop;
}

bool Player::existCountry (Country country){
    for(auto c : listCountry){
        if(c->getNameCountry() == country.getNameCountry())
            return true;
    }

    return false;
}

void Player::setStatus(GameStatus status){
    this->status = status;
}

GameStatus Player::getStatus() const{
    return this->status;
}

int Player::continentBonusTroop ()
{
    int ameriqueN(0), ameriqueS(0), europe(0), afrique(0), oceanie(0), asie(0);
    int numberBonusTroop(3);

    if(listCountry.size() / 3 > 3){
        numberBonusTroop += (listCountry.size() / 3 - 3);
    }

    for(auto country : listCountry){
        int countryId = country->getNumberCountry();
        if(countryId < 9)
            ameriqueN += 1;
        else if (countryId < 13)
            ameriqueS += 1;
        else if (countryId < 19)
            afrique += 1;
        else if (countryId < 26)
            europe += 1;
        else if (countryId < 38)
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

const std::vector<Country*>& Player::getListCountry () const {
    return listCountry;
}

const std::vector<Card*>& Player::getListCard() const{
    return listCard;
}

int Player::getOrder () {
    return order;
}

}

