#include "Ai.h"
#include <iostream>
#include <chrono>
#include <engine.h>
#include <vector>

using namespace engine;
using namespace state;

namespace ai{

//les commandes 
Place aiPlace;
Attack aiAttack;
Reinforce aiReinforce; 
DistributeCard aiDistributecard;
UseCard aiUsecard;

//la liste de pays de joueur
std::vector<std::shared_ptr<Country>> aiCountries;




Ai::Ai() {
    status = state::PLAYING;
    type = state::BOT;
    difficulty = Difficulty::EASY;
    name = "BOT";
}

Ai::~Ai() {
    
}

Ai::Ai(int id){
    this->id = id;
    status = state::PLAYING;
    type = state::BOT;
    difficulty = Difficulty::EASY;
}

void Ai::setState(const std::shared_ptr<state::State>& state){
    this->state = state;
    aiAttack.setState(state);
    aiDistributecard.setState(state);
}

void Ai::setPlayer(const std::shared_ptr<state::Player>& player){
    this->player = player;
    aiPlace.setPlayer(player);
    aiAttack.setPlayer(player);
    aiReinforce.setPlayer(player);
    aiDistributecard.setPlayer(player);
    aiUsecard.setPlayer(player);
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
    aiCountries = player->getCountriesList();
    std::vector<std::shared_ptr<Country>> allCountries = state->getCountriesList();

    //un exemple comment le IA fonctionne 
    if(difficulty == Difficulty::EASY){
        //place
        
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

