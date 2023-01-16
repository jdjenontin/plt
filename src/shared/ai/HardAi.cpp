#include <iostream>
#include <algorithm>

#include "HardAi.h"

#define DEBUG 1;

using namespace std;
using namespace state;

namespace ai{

HardAi::HardAi(){

}

HardAi::HardAi(shared_ptr<State> a_state) : Ai(a_state){

}

HardAi::~HardAi(){

}

void HardAi::sortCountryByBSR()
{
    std::shared_ptr<state::State> temp = state;
    
    auto borderSecurityRatioCmp = [temp](std::shared_ptr<Country>& a, std::shared_ptr<Country>& b) {
        return Computation::borderSecurityRatio(temp, a) > Computation::borderSecurityRatio(temp, b); 
    };

    std::sort(countriesList.begin(), countriesList.end(), borderSecurityRatioCmp);
}
/**
 * @brief Place Troop in the country with the highest brs
*/
void HardAi::place(){
    #ifdef DEBUG
        std::cout << "Hard AI :" << __func__ << std::endl;
    #endif

    int bonusTroop = player->continentBonusTroop();

    while(bonusTroop>0){
        this->sortCountryByBSR();
        countriesList[0]->addTroop(1);
        bonusTroop--;
    }
}

void HardAi::attack(){
    double index = 0;
    this->sortCountryByBSR();

    std::vector<std::shared_ptr<Country>> attackCandidates;
    index = countriesList.size()/2;

    // 
    attackCandidates.assign(countriesList.begin()+index,countriesList.end());
    

}

void HardAi::reinforce(){
    
}

void HardAi::execute(shared_ptr<Player> a_player){
    #ifdef DEBUG
        std::cout << "Hard AI " << __func__ << std::endl;
    #endif
    player = a_player;
    countriesList = player->getCountriesList();
    place();
}

}
