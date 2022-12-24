// TO-Do reorganize includes 
// Remove List name
// Create card :: Maybe move JSON object to static variable 


#include "State.h"
#include <iostream>
#include <map>

#include <random>
#include <SFML/Graphics.hpp>

#include "Dice.h"
#include "Calculation.h"

#include "chrono"

#include <fstream>
#include <json/json.h>

using namespace std;
using namespace ai;

namespace state
{
    
State::State(){
    this->listname = {"Tom", "Bob", "Uriel", "Sam", "Yann"};
}

State::~State(){
    
}

void State::init()
{
    this->buildCountries();
    this->distributeCountries();
    this->distibuteTroops(); 
}

void State::IncrementTurn () {
    turn++;
}

const int & State::getTurn() const {
    return turn;
}


// TO-DO : Improve with XIAO
void State::ChangePlaying () {
    orderPlayer++;
    if(orderPlayer == (int)playersList.size()){
        orderPlayer = 0;
        IncrementTurn();
    }

    if(playersList[orderPlayer]->getCountriesList().size() == 0){
        orderPlayer++;
        playersList[orderPlayer]->setStatus(state::LOSE);
        if(orderPlayer == (int)playersList.size())
            orderPlayer = 0;
    }
}

const std::vector<std::shared_ptr<Country>>& State::getCountriesList() const{
    return countriesList;
}

const std::vector<Card*>& State::getCardsList() const{
    return cardsList;
}

const std::vector<std::shared_ptr<Player>> & State::getPlayersList() const{
    return playersList;
}

int State::getOrderPlayer() const{
    return orderPlayer;
}

void State::buildCountries(){

    std::ifstream file("../res/countries.json");
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        exit(1);
    }

    // Parse the JSON file
    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errors;
    if (!Json::parseFromStream(builder, file, &root, &errors)) {
        std::cerr << "Error parsing JSON: " << errors << std::endl;
        exit(1);
    }

    // Iterate through the keys and values
    for (const auto& key : root.getMemberNames()) {
        countriesList.push_back(std::shared_ptr<Country>(new Country(key, 
                                                                    root[key]["id"].asInt())));
    }

    std::sort(countriesList.begin(), countriesList.end(), state::Country::idComparaison);
}

void State::createPlayers(){
    for(int i = 0; i<nbOfPlayer; i++){
        playersList.push_back(std::shared_ptr<Player>(new Player(i)));
    }
}

void State::distributeCountries(){

    std::vector<std::shared_ptr<Country>> cp_countriesList = countriesList;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine(seed);

    std::shuffle(cp_countriesList.begin(), cp_countriesList.end(), rng);
    
    int i = 0;

    for(auto& country : cp_countriesList){
        playersList[i]->addCountry(country);
        i++;
        i%=nbOfPlayer;
    }

}

void State::distibuteTroops(){
    
    // TO-DO : Make it a const
    map<int, int> initialTroopMap {{2,45}, {3,35}, {4,30}, {5,25}};

    int initialTroop = initialTroopMap[nbOfPlayer + nbOfBot];

    for (int i = 0; i != nbOfPlayer + nbOfBot; i++){
        std::vector<std::shared_ptr<Country>> playerCountries = playersList[i]->getCountriesList();

        // On aurait pu le faire hors de la boucle mais le nombre de pays n'est pas tjr cst
        int minTroopPerTeritory = (int) initialTroop/playerCountries.size();

        for(auto country : playerCountries){
            country -> addTroop(minTroopPerTeritory);
        }

        int remainingTroop = initialTroop % playerCountries.size();
        
        // Ajout du nombre de troupe restant de façon aléatoire sur les territoires 
        Dice dice(0, playerCountries.size() - 1);
        for(int k = 0; k != remainingTroop; k++)
        {
            int electedCountry = dice.thrown();
            playerCountries[electedCountry]->addTroop(1);
        } 
    }
}

// TO-Do : Use ownerId instead !
// Player* State::belongsto (Country* country){
//     for(unsigned i = 0; i < playersList.size(); i++){
//         sf::Color c1 = playersList[i].getColor();   
//         sf::Color c2 = country->getColor();
//         if(c1.toInteger() == c2.toInteger())
//             return &playersList[i];
//     }

//     return {};
// }

} // namespace state
