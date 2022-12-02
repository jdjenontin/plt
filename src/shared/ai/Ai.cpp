#include "Ai.h"
#include <iostream>
#include <chrono>
#include <engine.h>

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
std::vector<state::Country*> lcountry;

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
    lcountry = player->getListCountry();

    //un exemple comment le IA fonctionne 
    if(difficulty == Difficulty::EASY){
        //place
        place.setcountry(lcountry[1]);
        int bonus_troop = player->continentBonusTroop();
        for(int i = 0; i < bonus_troop; i++){
            place.execute();
        }
        //attack
        std::vector<Country*> aiCountries = getListCountry();
        Dice aiDice(0,aiCountries.size()-1);  //This dice lets us choose a random attack country
        engine::Attack attack;

        Country* aiAttackCountry = aiCountries.at(aiDice.thrown());

        std::vector<Country*> aiAttackableCountries; //

        for(int i=0; i<42;i++) {
            if (aiAttackCountry->isAdjacent(i)) {
                aiAttackableCountries.push_back(lcountry[i]);
            }
        }

        aiDice = Dice(0,aiAttackableCountries.size()-1);

        //The ai will then choose a random neighbouring country to attack
        Country* aiDefCountry = aiAttackableCountries.at(aiDice.thrown());

        attack.setAttackCountry(aiAttackCountry);
        attack.setDefCountry(aiDefCountry);
        attack.multipleAttack();
        //reinforce
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

