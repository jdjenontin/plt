// TO-Do reorganize includes 

#include <fstream>
#include <json/json.h>
#include <unistd.h>
#include <iostream>
#include <map>
#include <chrono>
#include <random>

#include "State.h"
#include "Dice.h"
#include "Calculation.h"


using namespace std;
using namespace ai;

namespace state
{

const string jsonPath = "res/countries.json";


State::State(){

}

State::~State(){
    
}

void State::init()
{
    this->buildCountries();
    this->createPlayers();
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

const std::vector<std::shared_ptr<Card>>& State::getCardsList() const{
    return cardsList;
}

const std::vector<std::shared_ptr<Player>> & State::getPlayersList() const{
    return playersList;
}

int State::getOrderPlayer() const{
    return orderPlayer;
}

void State::buildCountries(){

    Json::Value root = FileOps::jsonParser(jsonPath);

    for (const auto& key : root.getMemberNames()) {
        countriesList.push_back(std::shared_ptr<Country>(new Country(key, 
                                                                    root[key]["id"].asInt(), 
                                                                    root[key]["continent"].asInt())));
        
    }

    std::sort(countriesList.begin(), countriesList.end(), state::Country::idComparaison);

}

void State::buildCards(){

    Json::Value root = FileOps::jsonParser(jsonPath);

    TypeCard cardTypes[] = {Cavalry, Artillery, Infantry};

    for (const auto& key : root.getMemberNames()) {
        int typeId = root[key]["card"].asInt();
        cardsList.push_back(std::shared_ptr<Card>(new Card(key,
                                                            cardTypes[typeId])));
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine(seed);
    std::shuffle(cardsList.begin(), cardsList.end(), rng);
}

void State::createPlayers(){
    for(int i = 0; i<nbOfPlayer; i++){
        playersList.push_back(std::shared_ptr<Player>(new Player(i)));
    }

    for(int i = nbOfPlayer; i < (nbOfPlayer+nbOfBot); i++){
        playersList.push_back(std::shared_ptr<Player>(new Ai(i)));
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
        i%=(nbOfPlayer+nbOfBot);
    }

}

void State::distibuteTroops(){
    
    // TO-DO : Make it a const

    // Depending on the number of player, the initial troop for each player vary
    map<int, int> initialTroopMap {{2,45}, {3,35}, {4,30}, {5,25}};

    int initialTroop = initialTroopMap[nbOfPlayer + nbOfBot];

    for (int i = 0; i != nbOfPlayer + nbOfBot; i++){
        std::vector<std::shared_ptr<Country>> playerCountries = playersList[i]->getCountriesList();

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
