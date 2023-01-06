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

//Liste de tous les pays
std::vector<std::string> countriesNames = {"Alaska", "Territoire du Nord-Ouest", "Alberta", "Ontario", "Groenland", "Quebec", "Ouest des Etat-Unis", "Est des Etats-Unis", 
                        "Amerique Centrale", "Venezuela", "Perou", "Bresil", "Argentine", "Afrique du Nord", "Egypte", "Afrique de l'Est",
                         "Congo", "Afrique du Sud", "Madagascar", "Islande", "Grande-Bretagne", "Scandinavie", "Europe du Nord",
                          "Ukraine", "Europe de l'Ouest", "Europe du Sud", "Moyen-Orient", "Afghanistan", "Ural", "Siberie", "Yakutsk",
                           "Irkoutsk", "Mongolie", "Kamchatka", "Japon", "Chine", "Inde", "Siam", "Indonesie", "Nouvelle-Guinee", "Australie Orientale",
                            "Australie Occidentale"};


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

/*void Ai::setState(const std::shared_ptr<state::State>& state){
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

