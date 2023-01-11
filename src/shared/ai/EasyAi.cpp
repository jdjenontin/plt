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
extern Engine aiEngine; // Why ?
extern Place aiPlace;
extern Attack aiAttack;
extern Reinforce aiReinforce; 
extern DistributeCard aiDistributecard; // Why ?
extern UseCard aiUsecard;

Dice aiDice(1,6);

namespace ai{

EasyAi::EasyAi() {

}

EasyAi::~EasyAi() {
    
}

EasyAi::EasyAi(shared_ptr<State> a_state) : Ai(a_state){
    
}


// TO-DO : Delete 
void EasyAi::execute (){
    Dice reAttack(0,1); // Why ?
    int numConqueredCountries = 0; // Why ?

    vector<shared_ptr<Country>> aiAttackCountries; // Why ?
    cout << "Execute bot Easy" << endl;
    place();
    attack();
    //reinforce();
}

void EasyAi::execute(shared_ptr<Player> a_player)
{
    player = a_player;
    place();
    attack();
    //reinforce();
}

void EasyAi::place() {

    countriesList = player->getCountriesList();
    #ifdef DEBUG
        cout << "Place du bot" << endl;
    #endif

    aiDice.updateDice(0,player->getCountriesList().size()-1);
    shared_ptr<state::Country> country = countriesList.at(aiDice.thrown());

    int bonus_troop = player->continentBonusTroop();

    for(int i = 0; i < bonus_troop; i++){
        country->addTroop(1);
        bonus_troop--;
        country = countriesList.at(aiDice.thrown());
    }  
}

void EasyAi::attack() {

    countriesList = player->getCountriesList();
    
    cout << "Attack du bot" << endl;

    canAttack = false; // Why ?

    vector<int> count;
    vector<shared_ptr<Country>> aiAttackCountries;
    vector<shared_ptr<Country>> aiAttackableCountries; // We create a list with all the countries the Ai can attack with its attack Country


    // TO-DO Improve using find_if algo 
    for (int i=0; i<countriesList.size();i++) {
        if (countriesList.at(i)->getNumberOfTroop() > 1) {
            aiAttackCountries.push_back(countriesList.at(i));
        }
    }

    // TO-DO : Use Computation's functions instead
    //We make a list of all the countries we can attack
    for(int j=0; j<aiAttackCountries.size(); j++){
        for(int i=0; i<42;i++) {
            if (aiAttackCountries.at(j)->isAdjacent(i) & !Calculation::isCountryInList(v_listcountry.at(i), aiAttackCountries)) {
                cout << "The AI can attack " << v_listcountry.at(i)->getName() << ". \n";
                aiAttackableCountries.push_back(v_listcountry.at(i));
                count.push_back(j);
            }
        }
    }

    //If the ai can attack a country it will
    if (!aiAttackableCountries.empty()) {
        aiDice.updateDice(0,aiAttackableCountries.size()-1);

        //The ai will then choose a random neighbouring country to attack
        int rand = aiDice.thrown();
        shared_ptr<state::Country> aiAttackCountry = aiAttackCountries.at(count.at(rand));
        shared_ptr<state::Country> aiDefCountry = aiAttackableCountries.at(rand); 

        aiAttack.setAttackCountry(aiAttackCountry);
        aiAttack.setDefCountry(aiDefCountry);
        aiDice.updateDice(0, 3);
        
        aiAttack.setPlayer(player);
        
        aiAttack.execute();

    }
}

void EasyAi::reinforce() {
    countriesList = player->getCountriesList();
    cout << "Reinforce du bot" << endl;
    aiDice.updateDice(0,countriesList.size()-1);
    shared_ptr<state::Country> depatureCountry  = countriesList[aiDice.thrown()];

    aiReinforce.setM_country(depatureCountry);
    aiReinforce.setN_country(countriesList[aiDice.thrown()]);

    aiDice.updateDice(0, depatureCountry->getNumberOfTroop() - 1);

    for(int i = 0; i < aiDice.thrown(); i++)
    {
        aiReinforce.execute();
        cout << "Reinforcing" << endl;
    }
}

}