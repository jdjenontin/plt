#include "Country.h"
#include <iostream>

using namespace std;

namespace state{

std::vector<std::vector<bool>> Country::matriceAdj = FileOps::csvParser("res/adjacentMat.txt");

Country::Country (std::string a_name , int a_id) {
    name = a_name;
    id = a_id;
}

Country::Country (std::string a_name , int a_id, int cont) {
    name = a_name;
    id = a_id;
    continent = (Continent) cont;
}

Country::Country (std::string a_name , int a_id, int a_posX, int a_posY)
{
    Country(a_name, a_id);
    posX = a_posX;
    posY = a_posY;
}

Country::Country (std::string a_name, int a_id, state::Continent a_continent, std::vector<int> a_adjacentCountries)
    : Country(a_name, a_id)
{
    continent = a_continent;
    adjacentCountries = a_adjacentCountries;
}

Country::Country()
{
    
}

Country::~Country () {

}

bool Country::isAdjacent (int a_idCountry) {
    return matriceAdj[id][a_idCountry];
}

int Country::getNumberOfTroop() const {
    return numberOfTroop;
}

int Country::getId () const {
    return id;
}

const std::string& Country::getName() const{
    return name;
}

int Country::getOwnerId() const{
    return ownerId;
}
void Country::setOwnerId(int a_ownerId){
    ownerId = a_ownerId;
}

void Country::setNumberOfTroop (int a_nbTroop) {
    numberOfTroop = a_nbTroop;
}

void Country::addTroop (int a_nbTroop) {
    numberOfTroop += a_nbTroop;
}

void Country::reduceTroop (int a_nbTroop) {
    numberOfTroop -= a_nbTroop;
}

state::Continent Country::getContinent() const{
    return continent;
}
int Country::getPosX() const{
    return this->posX;
}

const std::vector<int>& Country::getAdjacentCountries() const {
    return adjacentCountries;
}
int Country::getPosY() const{
    return this->posY;
}

/**
 * @brief Compare 2 countries using their number of troop
*/
bool Country::troopComparaison(std::shared_ptr<Country>& a, std::shared_ptr<Country>& b)
{
    return a->numberOfTroop < b->numberOfTroop;
}

/**
 * @brief Compare 2 countries using their ids
*/
bool Country::idComparaison(std::shared_ptr<Country>& a, std::shared_ptr<Country>& b)
{
    return a->id < b->id;
}

/**
 * @brief Print the country keys informations
*/
void Country::print()
{
    std::cout << "----"<< name << " : " << id << "----"<<std::endl;
    std::cout << "Number of troop: " << numberOfTroop << std::endl;
    std::cout << "Owner          : " << ownerId << std::endl;
}

Json::Value Country::serialize(){
    Json::Value country;
    country["id"] = id;
    country["ownerId"] = ownerId;
    country["troop"] = numberOfTroop;

    return country;

}

void Country::setContinent(Continent cont){
    continent = cont;
}
