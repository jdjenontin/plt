#include "EasyAi.h"
#include <iostream>
#include <chrono>
#include <engine.h>
#include <vector>
#include <thread>


using namespace engine;
using namespace state;
using namespace std::this_thread;
using namespace std::chrono;
using namespace std;

extern vector<shared_ptr<state::Country>> v_listcountry;
extern Engine aiEngine;
extern Place aiPlace;
extern Attack aiAttack;
extern Reinforce aiReinforce; 
extern DistributeCard aiDistributecard;
extern UseCard aiUsecard;

Dice aiDice(1,6);

namespace ai{

EasyAi::EasyAi() {
    status = state::PLAYING;
    type = state::BOT;
    difficulty = Difficulty::EASY;
    name = "BOT";
}

EasyAi::~EasyAi() {
    
}

EasyAi::EasyAi(int id){
    this->id = id;
    status = state::PLAYING;
    type = state::BOT;
    difficulty = Difficulty::EASY;
}

void EasyAi::execute (const std::shared_ptr<state::Player>& currentPlayer){
    Dice reAttack(0,1);
    int numConqueredCountries = 0;

    std::vector<std::shared_ptr<Country>> aiAttackCountries;
    std::cout << "Execute bot Easy" << std::endl;
    place();
    attack(currentPlayer);
    //reinforce();
}

void EasyAi::place() {
    
    std::cout << "Place du bot" << std::endl;
    aiDice.updateDice(0,countriesList.size()-1);
    std::shared_ptr<state::Country> country = countriesList.at(aiDice.thrown());

    int bonus_troop = this->continentBonusTroop();

    for(int i = 0; i < bonus_troop; i++){
        country->addTroop(1);
        bonus_troop--;
        country = countriesList.at(aiDice.thrown());
        std::cout << "Ai execute" << std::endl;
    }  
}

void EasyAi::attack(const std::shared_ptr<state::Player>& currentPlayer) {

    std::cout << "Attack du bot" << std::endl;
    canAttack = false;
    std::vector<int> count;
    std::vector<std::shared_ptr<Country>> aiAttackCountries;
    std::vector<std::shared_ptr<Country>> aiAttackableCountries; // We create a list with all the countries the Ai can attack with its attack Country

    for (int i=0; i<countriesList.size();i++) {
        if (countriesList.at(i)->getNumberOfTroop() > 1) {
            aiAttackCountries.push_back(countriesList.at(i));
        }
    }

    //We make a list of all the countries we can attack
    for(int j=0; j<aiAttackCountries.size(); j++){
        for(int i=0; i<42;i++) {
            if (aiAttackCountries.at(j)->isAdjacent(i) & !Calculation::isCountryInList(v_listcountry.at(i), aiAttackCountries)) {
                std::cout << "The AI can attack " << v_listcountry.at(i)->getName() << ". \n";
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
        std::shared_ptr<state::Country> aiAttackCountry = aiAttackCountries.at(count.at(rand));
        std::shared_ptr<state::Country> aiDefCountry = aiAttackableCountries.at(rand); 



        std::cout << "The AI will attack " << aiDefCountry->getName() << " with " << aiAttackCountry->getName() << "\n";
        cout << aiDefCountry->getId() << endl;

        aiAttack.setAttackCountry(aiAttackCountry);
        std::cout << "Set Attack Country" << "\n";
        aiAttack.setDefCountry(aiDefCountry);
        std::cout << "Set def country" << "\n";
        aiDice.updateDice(0, 3);
        
        aiAttack.setPlayer(currentPlayer);
        
        aiAttack.execute();

        std::cout << "Attacking" << std::endl;

        std::cout << "End of Attack" << "\n";
    }
}

void EasyAi::reinforce() {

    std::cout << "Reinforce du bot" << std::endl;
    aiDice.updateDice(0,countriesList.size()-1);
    std::shared_ptr<state::Country> depatureCountry  = countriesList[aiDice.thrown()];

    aiReinforce.setM_country(depatureCountry);
    aiReinforce.setN_country(countriesList[aiDice.thrown()]);

    aiDice.updateDice(0, depatureCountry->getNumberOfTroop() - 1);

    for(int i = 0; i < aiDice.thrown(); i++)
    {
        aiReinforce.execute();
        std::cout << "Reinforcing" << std::endl;
    }
}

}