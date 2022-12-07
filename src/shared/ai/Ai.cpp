#include "Ai.h"
#include <iostream>
#include <chrono>
#include <engine.h>
#include <vector>

using namespace engine;
using namespace state;

namespace ai{

//les commandes 
Place place;
Attack attack;
Reinforce reinforce; 
DistributeCard distributecard;
UseCard usecard;

//la liste de pays de joueur
std::vector<state::Country*> aiCountries;

//Liste de tous les pays
std::vector<std::string> countriesNames = {"Alaska", "Territoire du Nord-Ouest", "Alberta", "Ontario", "Groenland", "Quebec", "Ouest des Etat-Unis", "Est des Etats-Unis", 
                        "Amerique Centrale", "Venezuela", "Perou", "Bresil", "Argentine", "Afrique du Nord", "Egypte", "Afrique de l'Est",
                         "Congo", "Afrique du Sud", "Madagascar", "Islande", "Grande-Bretagne", "Scandinavie", "Europe du Nord",
                          "Ukraine", "Europe de l'Ouest", "Europe du Sud", "Moyen-Orient", "Afghanistan", "Ural", "Siberie", "Yakutsk",
                           "Irkoutsk", "Mongolie", "Kamchatka", "Japon", "Chine", "Inde", "Siam", "Indonesie", "Nouvelle-Guinee", "Australie Orientale",
                            "Australie Occidentale"};


Ai::Ai() {
    status = state::PLAYING;
    typeplayer = state::BOT;
    difficulty = Difficulty::EASY;
}

Ai::~Ai() {
    
}

Ai::Ai(int order){
    this->order = order;
    status = state::PLAYING;
    typeplayer = state::BOT;
    difficulty = Difficulty::EASY;
}

void Ai::setState (state::State* state){
    this->state = state;
    attack.setState(state);
    distributecard.setState(state);
}

void Ai::setPlayer (state::Player* player){
    this->player = player;
    place.setPlayer(player);
    attack.setPlayer(player);
    reinforce.setPlayer(player);
    distributecard.setPlayer(player);
    usecard.setPlayer(player);
}

void Ai::setDifficulty(Difficulty difficulty){
    this->difficulty = difficulty;
}

Difficulty Ai::getDifficulty() const{
    return this->difficulty;
}

void Ai::execute (Difficulty difficulty){
    
    Dice reAttack(0,1);
    Calculation cal;
    int aiCanAttack = 1;
    int willAttack = 1;
    aiCountries = player->getListCountry();
    std::vector<Country*> allCountries = state->getListCountires();

    //un exemple comment le IA fonctionne 
    if(difficulty == Difficulty::EASY){
        //place
        Dice aiDice(0,aiCountries.size()-1);
        place.setcountry(aiCountries[aiDice.thrown()]);
        int bonus_troop = player->continentBonusTroop();
        for(int i = 0; i < bonus_troop; i++){
            place.execute();
        }

        //attack
        while (willAttack and aiCanAttack) {
            aiCanAttack = 0;
            aiDice.updateDice(0,aiCountries.size()-1);  //This dice lets us choose a random attack country

            Country* aiAttackCountry = aiCountries.at(aiDice.thrown());

            std::vector<Country*> aiAttackableCountries; // We create a list with all the countries the Ai can attack with its attack Country

            while(aiAttackCountry->getNumberTroop() == 1) {
                aiAttackCountry = aiCountries.at(aiDice.thrown());
            }   

            for(int i=0; i<42;i++) {
                if (aiAttackCountry->isAdjacent(i) & !Calculation::isCountryInList(allCountries.at(i), aiCountries)) {
                    std::cout << "The AI can attack " << allCountries.at(i)->getNameCountry() << ". \n";
                    aiAttackableCountries.push_back(allCountries.at(i));
                }
            }
            
            Dice aiAttackDice(0,aiAttackableCountries.size()-1);

            //The ai will then choose a random neighbouring country to attack
            
            Country* aiDefCountry = aiAttackableCountries.at(aiAttackDice.thrown());

            std::cout << "The AI will attack " << aiDefCountry->getNameCountry() << " with " << aiAttackCountry->getNameCountry() << "\n";

            attack.setAttackCountry(aiAttackCountry);
            attack.setDefCountry(aiDefCountry);
            aiDice.updateDice(0, 3);

            //The will randomly do a single, double, triple or multiple attack
            if (aiDice.thrown() == 0){
                attack.soloAttack();
            }

            else if (aiDice.thrown() == 1){
                attack.doubleAttack();
            }

            else if (aiDice.thrown() == 2){
                attack.tripleAttack();
            }

            else attack.multipleAttack();
            
            willAttack = reAttack.thrown();
            for (int i = 0; i<aiCountries.size()-1;i++) {
                if(aiCountries.at(i)->getNumberTroop() > 1) {
                    aiCanAttack = 1;
                }
            }
            std::cout << "Attacking" << std::endl;
        }

        //reinforce

        aiDice.updateDice(0,aiCountries.size()-1);
        state::Country* depatureCountry  = aiCountries[aiDice.thrown()];

        reinforce.setm_country(depatureCountry);
        reinforce.setn_country(aiCountries[aiDice.thrown()]);

        aiDice.updateDice(0, depatureCountry->getNumberTroop() - 1);
        
        for(int i = 0; i < aiDice.thrown(); i++)
        {
            reinforce.execute();
            std::cout << "Reinforcing" << std::endl;
        }
        
    }


    else if(difficulty == Difficulty::NORMAL){

    }

    else if(difficulty == Difficulty::HARD){
        
    }
    else if(difficulty == Difficulty::INSANE){

    }
}

void Ai::placeTroop(){

}

}

