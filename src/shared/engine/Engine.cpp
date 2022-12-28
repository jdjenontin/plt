#include <iostream>

#include "Engine.h"

#define DEBUG 1

namespace engine {

int bonus_troop;

Engine::Engine(){

}

Engine::~Engine(){
    
}

void Engine::usecard_execute(){
    usecard.execute();
    bonus_troop = usecard.getM_bonusTroop();
}

void Engine::distribute_execute(){
    distributecard.execute();
}

int Engine::reinforceN_execute(){
#ifdef DEBUG
    std::cout << "function :" << __func__ << std::endl;
#endif
    reinforce.setN_country(country);
    return reinforce.execute();
}

int Engine::reinforceM_execute(){
#ifdef DEBUG
    std::cout << "function :" << __func__ << std::endl;
#endif
    if(country->getNumberOfTroop() > 1)
        reinforce.setM_country(country);
    else return 0;
    return 1;
}

int Engine::attackD_execute(){
    attack.setDefCountry(country);
    if(attack.isAdjacent()){
        attack.execute();
    }
    else return 0;

    return 1;
}

int Engine::attackA_execute(){
    if(country->getNumberOfTroop() > 1)
        attack.setAttackCountry(country);
    else return 0;

    return 1;
}

void Engine::place_execute(){
    place.setCountry(country);
    place.execute();
}

void Engine::init (std::shared_ptr<state::State>& state){
    this->state = state;
    attack.setState(state);
    distributecard.setState(state);
}

void Engine::setPlayer (std::shared_ptr<state::Player>& player){
    place.setPlayer(player);
    attack.setPlayer(player);
    reinforce.setPlayer(player);
    distributecard.setPlayer(player);
    usecard.setPlayer(player);
}

void Engine::setCountry(const std::shared_ptr<state::Country>& country){
    this->country = country;
}

/**
 * @brief For the process place
*/
int Engine::getBonus_troop(){
    return bonus_troop;
}

/**
 * @brief The different process in the game
 * @param status For different process
 * @return Detect if the process execute successfully, if yes reuturn 1, if not return 0
*/
int Engine::execute(int status){
#ifdef DEBUG
    std::cout << "function :" << __func__ << std::endl;
#endif
    switch (status)
    {
    case 0:
    place_execute();
        break;
    case 1:
    return attackA_execute();
        break;
    case 2:
    return attackD_execute();
        break;
    case 3:
    return reinforceM_execute();
        break;
    case 4:
    return reinforceN_execute();
        break;
    case 5:
    distribute_execute();
        break; 
    case 6:
    usecard_execute();
        break; 
    case 7:
    attack.moveTroop();
    default:
        break;
    }

    return 1;
}


}