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
#include <algorithm>

using namespace std;

namespace state
{

const string jsonPath = "res/countries.json";


State::State(){
    nbOfBot.assign(3, 0);
}

State::~State(){
    
}

void State::init()
{
    this->buildCountries();
    this->buildCards();
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
        playersList[orderPlayer]->setStatus(LOSE);
        orderPlayer++;
        if(orderPlayer == (int)playersList.size())
            orderPlayer = 0;
    }
}

void State::addPlayer(){
    if(nbOfPlayer+nbOfBot[0]+nbOfBot[1]+nbOfBot[2] < 5)
        nbOfPlayer++;
}

void State::deletePlayer(){
    if(nbOfPlayer > 1)
        nbOfPlayer--;
}

void State::addBot(int difficulty){
    if(nbOfPlayer+nbOfBot[0]+nbOfBot[1]+nbOfBot[2] < 5)
        nbOfBot[difficulty]++;
}

void State::deleteBot(int difficulty){
    if(nbOfBot[difficulty] > 0)
        nbOfBot[difficulty]--;
}

const std::vector<std::shared_ptr<Country>>& State::getCountriesList() const{
    return countriesList;
}

const std::vector<std::shared_ptr<Card>>& State::getCardsList() const{
    return cardsList;
}

const std::vector<std::shared_ptr<Player>>& State::getPlayersList() const{
    return playersList;
}

int State::getOrderPlayer() const{
    return orderPlayer;
}

void State::buildCountries(){

    Json::Value root = FileOps::jsonParser(jsonPath);

    for (const auto& key : root.getMemberNames()) {
        Continent cont = (Continent )root[key]["Continent"].asInt();
        
        vector<int> adj;
        Json::Value adjJson = root[key]["Ajacent"];

        for (unsigned int i = 0; i < adjJson.size(); i++) {
            adj.push_back(adjJson[i].asInt());
        }
        countriesList.push_back(std::shared_ptr<Country>(new Country(key, 
                                                                    root[key]["id"].asInt(),
                                                                    cont,
                                                                    adj)));
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
    int n = nbOfPlayer+nbOfBot[0]+nbOfBot[1]+nbOfBot[2];
    for(int i = 0; i<n; i++){
        if(i < nbOfPlayer)
            playersList.push_back(std::shared_ptr<Player>(new Player(i)));
        else if(i < nbOfPlayer+nbOfBot[0])
            playersList.push_back(std::shared_ptr<Player>(new Player(i, state::EASYBOT)));
        else if(i < nbOfPlayer+nbOfBot[0]+nbOfBot[1])
            playersList.push_back(std::shared_ptr<Player>(new Player(i, state::NORMALBOT)));
        else if(i < nbOfPlayer+nbOfBot[0]+nbOfBot[1]+nbOfBot[2])
            playersList.push_back(std::shared_ptr<Player>(new Player(i, state::HARDBOT)));
    }
}

void State::distributeCountries(){

    std::vector<std::shared_ptr<Country>> cp_countriesList = countriesList;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine(seed);

    std::shuffle(cp_countriesList.begin(), cp_countriesList.end(), rng);

    int i = 0;
    int n = nbOfPlayer+nbOfBot[0]+nbOfBot[1]+nbOfBot[2];
    for(auto& country : cp_countriesList){
        playersList[i]->addCountry(country);
        i++;
        i%=n;
    }

}

void State::distibuteTroops(){
    
    // TO-DO : Make it a const

    // Depending on the number of player, the initial troop for each player vary
    int n = nbOfPlayer+nbOfBot[0]+nbOfBot[1]+nbOfBot[2];
    map<int, int> initialTroopMap {{2,45}, {3,35}, {4,30}, {5,25}};

    int initialTroop = initialTroopMap[n];

    for (int i = 0; i != n; i++){
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
