#include "Ai.h"
#include <iostream>
#include <chrono>
#include "engine.h"
#include <vector>

using namespace engine;
using namespace state;


// TO-DO : Chnage those to attributes


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
    //aiDistributecard.setState(state); //Important ??
}

void Ai::setPlayer(const std::shared_ptr<state::Player>& player){
    this->player = player;
    aiPlace.setPlayer(player);
    aiAttack.setPlayer(player);
    aiReinforce.setPlayer(player);
    //aiDistributecard.setPlayer(player); //Important ?
    aiUseCard.setPlayer(player);
}

void Ai::setDifficulty(Difficulty difficulty){
    this->difficulty = difficulty;
}

Difficulty Ai::getDifficulty(){
    return this->difficulty;
}

}

