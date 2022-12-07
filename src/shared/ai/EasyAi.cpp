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

namespace ai{

extern Place aiPlace;
extern Attack aiAttack;
extern Reinforce aiReinforce; 
extern DistributeCard aiDistributecard;
extern UseCard aiUsecard;

EasyAi::EasyAi() {

}

EasyAi::~EasyAi() {

}

void EasyAi::execute() {
    Dice reAttack(0,1);
    int aiCanAttack = 1;
    int willAttack = 1;
    std::vector<state::Country*> aiCountries = player->getListCountry();
    std::vector<state::Country*> allCountries = state->getListCountires();
    std::vector<state::Country*> aiAttackCountries;
    int numConqueredCountries = 0;

    //place
    Dice aiDice(0,aiCountries.size()-1);
    aiPlace.setcountry(aiCountries.at(aiDice.thrown()));
    int bonus_troop = player->continentBonusTroop();
    for(int i = 0; i < bonus_troop; i++){
        aiPlace.execute();
    }

    sleep_for(milliseconds(100));

    //attack
    while (willAttack and aiCanAttack) {
        aiCanAttack = 0;
        std::vector<int> count = {};

        std::vector<state::Country*> aiAttackableCountries; // We create a list with all the countries the Ai can attack with its attack Country

        for (long unsigned int i=0; i<aiCountries.size();i++) {
            if (aiCountries.at(i)->getNumberTroop() > 1) {
                aiAttackCountries.push_back(aiCountries.at(i));
            }
        }

        //We make a list of all the countries we can attack
        for(long unsigned int j=0; j<aiAttackCountries.size(); j++){
            for(int i=0; i<42;i++) {
                if (aiAttackCountries.at(j)->isAdjacent(i) & !Calculation::isCountryInList(allCountries.at(i), aiAttackCountries)) {
                    std::cout << "The AI can attack " << allCountries.at(i)->getNameCountry() << ". \n";
                    aiAttackableCountries.push_back(allCountries.at(i));
                    count.push_back(j);
                }
            }
        }
        
        //If the ai can attack a country it will
        if (!aiAttackableCountries.empty()) {
            aiDice.updateDice(0,aiAttackableCountries.size()-1);

            //The ai will then choose a random neighbouring country to attack
            int rand = aiDice.thrown();
            aiAttackCountry = aiAttackCountries.at(count.at(rand));
            aiDefCountry = aiAttackableCountries.at(rand);

            

            std::cout << "The AI will attack " << aiDefCountry->getNameCountry() << " with " << aiAttackCountry->getNameCountry() << "\n";

            aiAttack.setAttackCountry(aiAttackCountry);
            aiAttack.setDefCountry(aiDefCountry);
            aiDice.updateDice(0, 3);
            int selectAttack = aiDice.thrown();

            //The will randomly do a single, double, triple or multiple attack
            if ( selectAttack == 0) numConqueredCountries += aiAttack.soloAttack();
                

            else if (selectAttack == 1 and ((aiDefCountry->getNumberTroop()==1 and aiAttackCountry->getNumberTroop()==2)  or aiAttackCountry->getNumberTroop()>2)){
                numConqueredCountries += aiAttack.doubleAttack();
            }

            else if (selectAttack == 2 and aiAttackCountry->getNumberTroop()>2) numConqueredCountries += aiAttack.tripleAttack();

            else if (selectAttack == 3) numConqueredCountries += aiAttack.multipleAttack();

            else if (aiAttackCountry->getNumberTroop()>2) numConqueredCountries += aiAttack.soloAttack();
            
            willAttack = reAttack.thrown();
            for (long unsigned int i = 0; i<aiAttackCountries.size()-1;i++) {
                if(aiAttackCountries.at(i)->getNumberTroop() > 1) {
                    aiCanAttack = aiCanAttack | 1;
                }
            }
            
            std::cout << "Attacking" << std::endl;
            if (numConqueredCountries) {
                conqueredCountries.push_back(aiDefCountry);
            }
            

        }
        aiAttackableCountries.clear();

        for(long unsigned int i =0; i<aiAttackableCountries.size(); i++) delete aiAttackableCountries.at(i);
        sleep_for(milliseconds(100));
    }

    sleep_for(milliseconds(100));

    aiAttackCountries.clear();
    //We deallocate the memory because the vector class does not deallocate automatically
    for(long unsigned int i =0; i<aiAttackCountries.size(); i++) delete aiAttackCountries.at(i);

    //reinforce

    aiDice.updateDice(0,aiCountries.size()-1);
    state::Country* depatureCountry  = aiCountries[aiDice.thrown()];

    aiReinforce.setm_country(depatureCountry);
    aiReinforce.setn_country(aiCountries[aiDice.thrown()]);

    aiDice.updateDice(0, depatureCountry->getNumberTroop() - 1);
    
    for(int i = 0; i < aiDice.thrown(); i++)
    {
        aiReinforce.execute();
        std::cout << "Reinforcing" << std::endl;
    }
    
}

}