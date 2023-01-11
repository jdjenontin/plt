#include "Ai.h"
#include <iostream>
#include <chrono>
#include "engine.h"
#include <vector>

using namespace engine;
using namespace state;


// TO-DO : Chnage those to attributes

//les commandes 
Engine aiEngine;
Place aiPlace;
Attack aiAttack;
Reinforce aiReinforce; 
DistributeCard aiDistributecard;
UseCard aiUsecard;

namespace ai{


std::vector<std::shared_ptr<Country>> aiCountries;

Ai::Ai() {
}

Ai::~Ai() {
    
}


Ai::Ai(std::shared_ptr<State> a_state){
    state = a_state;
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

Difficulty Ai::getDifficulty(){
    return this->difficulty;
}

}

