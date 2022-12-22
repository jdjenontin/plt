#include "Player.h"
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

namespace state{

Player::Player () {
    status = PLAYING;
    type = HUMAN;
}
//Tacitement le nombre de troup est 35 pour les 3 joueurs 

Player::Player (int a_id) {
    status = PLAYING;
    id = a_id;
    type = HUMAN;
}

Player::~Player () {

}

void Player::addCountry (Country* country) {
    countriesList.push_back(country);
}

void Player::deleteCountry (Country* country) {
    int i = 0;
    while(countriesList[i] -> getName() != country -> getName()){
        i++;
    }
    countriesList.erase(countriesList.begin() + i);
}

void Player::addCard (Card* card) {
    cardsList.push_back(card);
}

void Player::deleteCard (Card* card) {
    int i = 0;
    while(cardsList[i]->getName() != card->getName()){
        i++;
    }
    cardsList.erase(cardsList.begin() + i);
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
    for(auto c : countriesList){
        if(c->getName() == country.getName())
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

void Player::setName(const std::string& name){
    this->name = name;
}

const std::string& Player::getName() const{
    return this->name;
}

TypePlayer Player::getType() const{
    return this->type;
}

/**
 * @brief Compute the number of bonus troop
 * @return Number of bonus troop
*/
int Player::continentBonusTroop ()
{
    int numberBonusTroop(3);

    std::vector<int> r_presence(6,0);
    r_presence = this->presenceOnContinents();

    if(countriesList.size() / 3 > 3){
        numberBonusTroop += (countriesList.size() / 3 - 3);
    }


    // Ajout des troupes bonus
    if (r_presence[0] == 9) numberBonusTroop += 5;
    if (r_presence[1] == 4) numberBonusTroop += 2;
    if (r_presence[2] == 6) numberBonusTroop += 3;
    if (r_presence[3] == 7) numberBonusTroop += 5;
    if (r_presence[4] == 12) numberBonusTroop += 7;
    if (r_presence[5] == 4) numberBonusTroop += 2;

    return numberBonusTroop;
}

/**
 * @brief Get the number of country own by a specific player each continent
 * @param a_player A pointer on the player
 * @return vector with the number of countries in this id [Amérique du Nord, Amérique du sud, Afrique, Europe, Asie]
*/
std::vector<int> Player::presenceOnContinents(){
    
    std::vector<int> r_presence(6,0);
    
    for(auto country : countriesList)
    {
        int countryId = country->getId();
        if(countryId < 9)
            r_presence[0] += 1;
        else if (countryId < 13)
            r_presence[1] += 1;
        else if (countryId < 19)
            r_presence[2]+= 1;
        else if (countryId < 26)
            r_presence[3] += 1;
        else if (countryId < 38)
            r_presence[4] += 1;
        else 
            r_presence[5] +=1;
    }

    return r_presence;
}

const std::vector<Country*>& Player::getCountriesList () const {
    return countriesList;
}

const std::vector<Card*>& Player::getCardsList() const{
    return cardsList;
}

int Player::getOrder () {
    return id;
}

}

