#include <iostream>
#include <algorithm>

#include "HardAi.h"

#define DEBUG 1;

using namespace std;
using namespace state;
using namespace engine;

namespace ai{

HardAi::HardAi(){

}

HardAi::HardAi(shared_ptr<State> a_state) : Ai(a_state){

}

HardAi::~HardAi(){

}

bool HardAi::hasEnemyAdjacentCountry (std::vector<std::shared_ptr<state::Country>> countriesList){
    for(auto c : countriesList){
        if(!Computation::isCountryInList(c, countriesList))
            return true;
    }
    return false;
}

std::shared_ptr<state::Country> HardAi::extractCountryToReinforce (){
    std::vector<std::shared_ptr<state::Country>> extractCountryList;

    for(auto c : countriesList){
        if(!hasEnemyAdjacentCountry(Computation::adjacentCountries(state, c)))
            extractCountryList.push_back(c);
    }

    auto extractCountryCmp = [](std::shared_ptr<state::Country>& a, std::shared_ptr<state::Country>& b) {
        return a->getNumberOfTroop() > b->getNumberOfTroop(); 
    };

    std::sort(extractCountryList.begin(), extractCountryList.end(), extractCountryCmp);
    return extractCountryList[0];
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
    UseCard usecard;
    usecard.setState(state);
    usecard.setPlayer(player);
    usecard.execute();

    int bonusTroop = player->continentBonusTroop() + usecard.getM_bonusTroop();

    while(bonusTroop>0){
        this->sortCountryByBSR();
        countriesList[0]->addTroop(1);
        bonusTroop--;
    }
}

void HardAi::attack(){
    Attack attack;
    AttackRouteCalculation routeCal(state, countriesList);
    std::vector<std::shared_ptr<state::Country>> totalCountriesList = state->getCountriesList();

    attack.setState(state);
    attack.setPlayer(player);
    std::vector<std::vector<int>> route = routeCal.execute();
    if(route.empty()) {
        cout << "routeList nulle" << endl;
        return;
    }
    for(int i = 0; i < route[0].size(); i++){
#ifdef DEBUG
        std::cout << totalCountriesList[route[0][i]]->getName() << totalCountriesList[route[1][i]]->getName() << std::endl;
        std::cout << totalCountriesList[route[0][i]]->getNumberOfTroop() << totalCountriesList[route[1][i]]->getNumberOfTroop() << std::endl;
#endif
        std::shared_ptr<state::Country> att = totalCountriesList[route[0][i]];
        std::shared_ptr<state::Country> def = totalCountriesList[route[1][i]];
        attack.setAttackCountry(att);
        attack.setDefCountry(def);
        attack.execute();
        int attTroop = att->getNumberOfTroop();
        int moveTroop = route[6][i];
        if(moveTroop == 0) continue;
        else{
            int n = (attTroop > moveTroop) ? moveTroop : (attTroop-1);
            att->reduceTroop(n);
            def->addTroop(n);
        }
    }
}

void HardAi::reinforce(){
    std::shared_ptr<state::Country> country = extractCountryToReinforce();

    int nTroop = country->getNumberOfTroop();
    if(nTroop < 2) return;
    this->sortCountryByBSR();

    while(nTroop > 1){
        countriesList[0]->addTroop(1);
        country->reduceTroop(1);
        nTroop--;
    }
}

void HardAi::execute(shared_ptr<Player> a_player){
#ifdef DEBUG
    std::cout << "Hard AI " << __func__ << std::endl;
#endif
    player = a_player;
    countriesList = player->getCountriesList();
    place();
    attack();
    reinforce();
}

}
