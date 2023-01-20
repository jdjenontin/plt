#include "EasyAi.h"
#include <iostream>
#include <chrono>
#include <engine.h>
#include <vector>


using namespace engine;
using namespace state;
using namespace std;

// TO-DO Delete externs 

extern vector<shared_ptr<state::Country>> v_listcountry;


Dice aiDice(1,6);

namespace ai{

EasyAi::EasyAi() {

}

EasyAi::~EasyAi() {
    
}

EasyAi::EasyAi(shared_ptr<State> a_state) : Ai(a_state){
    
}


void EasyAi::execute(shared_ptr<Player> a_player)
{
    #ifdef DEBUG
        cout << "Executing bot " << __func__ << endl;
    #endif
    player = a_player;
    place();
    attack();
    reinforce();
}

void EasyAi::place() {

    countriesList = player->getCountriesList();
    #ifdef DEBUG
        cout << "Place du bot " << __func__ << endl;
    #endif

    aiDice.updateDice(0,player->getCountriesList().size()-1);
    int d1 = aiDice.thrown();
    if(d1 == -1) return;
    shared_ptr<state::Country> country = countriesList[d1];

    int bonus_troop = player->continentBonusTroop();

    for(int i = 0; i < bonus_troop; i++){
        country->addTroop(1);
        bonus_troop--;
        int d2 = aiDice.thrown();
        if(d2 == -1) return;
        country = countriesList.at(d2);
    }  
}

void EasyAi::attack() {

    countriesList = player->getCountriesList();

    vector<int> count;
    vector<shared_ptr<Country>> aiAttackCountries;
    vector<shared_ptr<Country>> aiAttackableCountries; // We create a list with all the countries the Ai can attack with its attack Country


    // TO-DO Improve using find_if algo 
    for (unsigned int i=0; i<countriesList.size();i++) {
        if (countriesList.at(i)->getNumberOfTroop() > 1) {
            aiAttackCountries.push_back(countriesList.at(i));
        }
    }

    // TO-DO : Use Computation's functions instead
    //We make a list of all the countries we can attack
    int idCountry;
    if(aiAttackCountries.empty()) return;

    aiDice.updateDice(0,aiAttackCountries.size()-1);
    idCountry = aiDice.thrown();
    aiAttackableCountries = Computation::adjacentCountries(state, aiAttackCountries[idCountry]);

    //If the ai can attack a country it will
    if (!aiAttackableCountries.empty()) {
        aiDice.updateDice(0,aiAttackableCountries.size()-1);

        //The ai will then choose a random neighbouring country to attack
        int rand = aiDice.thrown();
        if(rand == -1) return;
        shared_ptr<state::Country> aiAttackCountry = aiAttackCountries.at(idCountry);
        shared_ptr<state::Country> aiDefCountry = aiAttackableCountries.at(rand); 

        aiAttack.setAttackCountry(aiAttackCountry);
        aiAttack.setDefCountry(aiDefCountry);
        aiDice.updateDice(0, 3);
        
        aiAttack.setPlayer(player);
        
        int win = aiAttack.execute();
        if(win == 1){
            while(aiAttackCountry->getNumberOfTroop() > 1){
                aiAttackCountry->reduceTroop(1);
                aiDefCountry->addTroop(1);
            }
        }

    }
}

void EasyAi::reinforce() {
    #ifdef DEBUG
        cout << "Reinforce du bot " << __func__ << endl;
    #endif

    countriesList = player->getCountriesList();

    aiDice.updateDice(0,countriesList.size()-1);
    int d1 = aiDice.thrown();
    if(d1 == -1) return;
    shared_ptr<state::Country> depatureCountry  = countriesList[d1];

    aiReinforce.setM_country(depatureCountry);
    int d2 = aiDice.thrown();
    if(d2 == -1) return;
    aiReinforce.setN_country(countriesList[d2]);
    aiReinforce.setPlayer(player);

    for(int i = 0; i < depatureCountry->getNumberOfTroop()/2; i++)
    {
        aiReinforce.execute();
    }
}

}