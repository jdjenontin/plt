#include "Ai.h"
#include <iostream>

#include <engine.h>

using namespace engine;

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

