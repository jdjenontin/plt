#include "Ai.h"

#include <engine.h>

using namespace engine;

namespace ai{

Place place;
Attack attack;
Reinforce reinforce; 
DistributeCard distributecard;
UseCard usecard;

std::vector<state::Country*> listcountry;

Ai::Ai() {
    status = state::PLAYING;
    typeplayer = state::BOT;
}

Ai::~Ai() {
    
}

Ai::Ai(int order){
    this->order = order;
    status = state::PLAYING;
    typeplayer = state::BOT;
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

void Ai::setDifficulty (int dif){
    this->difficulty = dif;
}

void Ai::execute (int difficulty){
    listcountry = player->getListCountry();

    if(difficulty == 0){
        place.setcountry(listCountry[0]);
        for(int i = 0; i < player->continentBonusTroop(); i++){
            place.execute();
        }
    }
}

}