#include "State.h"
#include <iostream>
#include <map>

#include <random>
#include <SFML/Graphics.hpp>

#include "Dice.h"
#include "Calculation.h"

#include "chrono"

using namespace std;
using namespace ai;

namespace state
{
//Création de la liste de tous les pays
std::vector<std::string> countriesNames = {"Alaska", "Territoire du Nord-Ouest", "Alberta", "Ontario", "Groenland", "Quebec", "Ouest des Etat-Unis", "Est des Etats-Unis", 
                        "Amerique Centrale", "Venezuela", "Perou", "Bresil", "Argentine", "Afrique du Nord", "Egypte", "Afrique de l'Est",
                         "Congo", "Afrique du Sud", "Madagascar", "Islande", "Grande-Bretagne", "Scandinavie", "Europe du Nord",
                          "Ukraine", "Europe de l'Ouest", "Europe du Sud", "Moyen-Orient", "Afghanistan", "Ural", "Siberie", "Yakutsk",
                           "Irkoutsk", "Mongolie", "Kamchatka", "Japon", "Chine", "Inde", "Siam", "Indonesie", "Nouvelle-Guinee", "Australie Orientale",
                            "Australie Occidentale"};
    
State::State(){
    this->listname = {"Tom", "Bob", "Uriel", "Sam", "Yann"};
}

State::~State(){
    
}

void State::init()
{
    std::map <int, string> listcountry;

    // Création de la liste des joueurs
    for(int i = 0; i < numberPlayer; i++){
        Player p(i);

        p.setName(listname[i]);
        playersList.push_back(p);
    }

    for(int i = 0; i < numberBot; i++){
        Ai a(i);

        a.setName("Bot");
        playersList.push_back(a);
    }

    for(unsigned i = 0; i < playersList.size(); i++){
        listPlayers.push_back(&playersList[i]);
    }

    for(int i = 0; i < (int)countriesNames.size(); i++) {
        listcountry[i] = countriesNames[i];
    }

    for (map<int,string>::iterator it=listcountry.begin(); it!=listcountry.end(); ++it) {
        Country country(it->second, it->first);
        countriesList.push_back(country);
    }

    //Creation de la liste de toutes les cartes 
    for(int i = 0; i < 42; i+=3){
        Card card1(countriesNames[i], Infantry);
        cardList.push_back(card1);

        Card card2(countriesNames[i+1], Cavalry);
        cardList.push_back(card2);

        Card card3(countriesNames[i+2], Artillery);
        cardList.push_back(card3);
    }

    // Shuffle the card
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine(seed);
    std::shuffle(begin(cardList), end(cardList), rng);

    //Affectation des pays et troupes aux joueurs
    vector<int> affectation_order;
    Calculation calc;
    affectation_order = calc.shuffledTab(42);

    // Attribution des pays : Dans certains cas les premiers ont plus de pays que les derniers
    int j = 0;
    for(auto i : affectation_order){
        playersList[j].addCountry(&countriesList[i]);
        j++;
        j %= numberPlayer + numberBot;
    }
    
    // Attribution des soldats :
    
    map<int, int> initialTroopMap {{2,45}, {3,35}, {4,30}, {5,25}};

    int initialTroop = initialTroopMap[numberPlayer + numberBot];

    for (int i = 0; i != numberPlayer + numberBot; i++){
        vector<Country*> playerCountries = playersList[i].getCountriesLists();

        // On aurait pu le faire hors de la boucle mais le nombre de pays n'est pas tjr cst
        int minTroopPerTeritory = (int) initialTroop/playerCountries.size();

        // Ajout d'un nombre min de troupe à tous less territoire
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

    for(unsigned i = 0; i < countriesList.size(); i++){
        listCountires.push_back(&countriesList[i]);
    }

    for(unsigned i = 0; i < cardList.size(); i++){
        cardsList.push_back(&cardList[i]);
    }
}

void State::IncrementTurn () {
    turn++;
}

const int & State::getTurn() const {
    return turn;
}

void State::ChangePlaying () {
    orderPlayer++;
    if(orderPlayer == (int)playersList.size()){
        orderPlayer = 0;
        IncrementTurn();
    }

    if(playersList[orderPlayer].getCountriesLists().size() == 0){
        orderPlayer++;
        playersList[orderPlayer].setStatus(state::LOSE);
        if(orderPlayer == (int)playersList.size())
            orderPlayer = 0;
    }
}

const std::vector<Country*>& State::getListCountires() const{
    return listCountires;
}

const std::vector<Card*>& State::getCardsList() const{
    return cardsList;
}

const std::vector<Player*>& State::getListPlayers() const{
    return listPlayers;
}

int State::getOrderPlayer() const{
    return orderPlayer;
}

Player* State::belongsto (Country* country){
    for(unsigned i = 0; i < playersList.size(); i++){
        sf::Color c1 = playersList[i].getColor();   
        sf::Color c2 = country->getColor();
        if(c1.toInteger() == c2.toInteger())
            return &playersList[i];
    }

    return {};
}

} // namespace state
