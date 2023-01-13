#include <iostream>

#include "Engine.h"

#define DEBUG 1

#define PLACE 0
#define ATTACK_A 1
#define ATTACK_D 2
#define REINFORCE_M 3
#define REINFORCE_N 4
#define DISTRIBUTE 5
#define USECARD 6
#define SOLO_ATTACK 7
#define DOUBLE_ATTACK 8
#define MULTI_ATTACK 9

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
#ifdef DEBUG
    std::cout << "function :" << __func__ << std::endl;
#endif
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
#ifdef DEBUG
    std::cout << "function : " << __func__ << std::endl;
#endif 
    attack.setDefCountry(country);
    if(!attack.isAdjacent())
        return 0;
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
    case PLACE:
    place_execute();
        break;
    case ATTACK_A:
    return attackA_execute();
        break;
    case ATTACK_D:
    return attackD_execute();
        break;
    case REINFORCE_M:
    return reinforceM_execute();
        break;
    case REINFORCE_N:
    return reinforceN_execute();
        break;
    case DISTRIBUTE:
    distribute_execute();
        break; 
    case USECARD:
    usecard_execute();
        break;
    case SOLO_ATTACK:
    attack.setAttackType(AttackType::SOLO);
    return attack.execute();
    case DOUBLE_ATTACK:
    attack.setAttackType(AttackType::DOUBLE);
    return attack.execute();
    case MULTI_ATTACK:
    attack.setAttackType(AttackType::MULTIPLE);
    return attack.execute();           
    default:
        break;
    }

    return 1;
}


}