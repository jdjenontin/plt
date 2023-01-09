#include "Player.h"
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

namespace state{
// Constants variables
// TO-DO : Complete and change magic numbers 

const int totalAsia = 12;

std::vector<std::string> Player::defaultNames = {"Tom", "Bob", "Uriel", "Sam", "Yann"};

Player::Player () {
    status = PLAYING;
    type = HUMAN;
}
//Tacitement le nombre de troup est 35 pour les 3 joueurs 

Player::Player (int a_id) : Player() {
    id = a_id;
    name = defaultNames[a_id];
}

// TO-DO : think aout name implication
Player::Player(int a_id, TypePlayer a_type) :Player(a_id){
    type = a_type;
}

Player::~Player () {

}

void Player::addCountry (shared_ptr<state::Country>& a_country) {
    cout << "In add country" << endl;
    cout << "In add country for player id:" << id << endl;
    a_country->setOwnerId(id);
    cout << "set owner Id" << endl;
    countriesList.push_back(a_country);
    cout << "Pushed back" << endl;
}

void Player::deleteCountry (shared_ptr<state::Country>& a_country) {
    cout << "In delete country" << endl;
    int i = 0;
    while(countriesList[i] -> getId() != a_country -> getId()){
        i++;
    }
    a_country->setOwnerId(-1); // -1 error id
    countriesList.erase(countriesList.begin() + i);
}

void Player::addCard (shared_ptr<Card>& card) {
    cardsList.push_back(card);
}

void Player::deleteCard (shared_ptr<Card>& card) {
    int i = 0;
    while(cardsList[i]->getName() != card->getName()){
        i++;
    }
    cardsList.erase(cardsList.begin() + i);
}

// void Player::setColor(const sf::Color& m_color){
//     color = m_color;
// }

// const sf::Color& Player::getColor() const{
//     return color;
// }

const int & Player::getOwnTroop() const {
    return ownTroop;
}

// TO-DO : Indispensable ????

bool Player::existCountry (Country country){
    for(auto c : countriesList){
        if(c->getId() == country.getId())
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

void Player::setName(const string& name){
    this->name = name;
}

const string& Player::getName() const{
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

    vector<int> r_presence(6,0);
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
vector<int> Player::presenceOnContinents(){
    
    vector<int> r_presence(6,0);
    
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

const vector<shared_ptr<Country>>& Player::getCountriesList () const {
    return countriesList;
}

const vector<shared_ptr<Card>>& Player::getCardsList() const{
    return cardsList;
}

int Player::getId() const {
    return id;
}

void Player::print()
{
    cout << "---- " << "Player" << id << "----" << endl;
    cout << "Number of country : " << countriesList.size() << endl; 
    cout << "Number of card    : " << cardsList.size() << endl; 
    cout << "(Countries, troop)" << endl; 
    for(auto& country : countriesList){
        cout << "(" << country->getName() <<","<< country->getNumberOfTroop()<<") ";
    }

    cout<<endl;
}


}

