#include "Ai.h"
#include <iostream>
#include <chrono>
#include <engine.h>
#include <vector>

using namespace engine;
using namespace state;

//les commandes 
Engine aiEngine;
Place aiPlace;
Attack aiAttack;
Reinforce aiReinforce; 
DistributeCard aiDistributecard;
UseCard aiUsecard;

namespace ai{



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

/*
void Ai::setPlayer(const std::shared_ptr<state::Player>& player){
    this->player = player;
    aiPlace.setPlayer(player);
    aiAttack.setPlayer(player);
    aiReinforce.setPlayer(player);
    aiDistributecard.setPlayer(player);
    aiUsecard.setPlayer(player);
}*/

void Ai::setDifficulty(Difficulty difficulty){
    this->difficulty = difficulty;
}

Difficulty Ai::getDifficulty(){
    return this->difficulty;
}


void Ai::placeTroop(){

}

}

