#include "AttackRouteCalculation.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>  

// #define DEBUG 1

using namespace std;

namespace ai{

/* 
Dans le vector route, chaque element signfie : 
    route[0] : Pays attaquant
    route[1] : Pays defensif
    route[2] : Nombre de troups reste apres avoir attaque(Dans la condition ideal, on imagine que chaque attack le nombre de troup
               perdu est egale le nombre de troup de pays defensif plus 1)
    route[3] : Bonus de troup.
    route[4] : Nombre de fois de ce route a eu la probabilite entre PASS et SAFE
    route[5] : Indice de la route. On tient compte de la probabilite et le bonus de troup, et donc l'indice = route[3] - 2*route[4]
    route[6] : Nombre de troup a distribuer
*/

AttackRouteCalculation::AttackRouteCalculation(){

}

AttackRouteCalculation::~AttackRouteCalculation(){

}

AttackRouteCalculation::AttackRouteCalculation(std::shared_ptr<state::State> state, std::vector<std::shared_ptr<state::Country>> countriesList){
    this->state = state;
    this->countriesList = countriesList;
    this->totalCountriesList = state->getCountriesList();
}

std::vector<std::vector<int>> AttackRouteCalculation::createRoute (std::shared_ptr<state::Country> attCountry, std::shared_ptr<state::Country> defCountry,
                                                                   int condition, std::vector<std::vector<int>> m_route){
#ifdef DEBUG
    std::cout << "AttackRouteCalculation : " << __func__ << std::endl;
#endif
    vector<vector<int>> route(7);
    if(m_route.empty()){
        route[0].push_back(attCountry->getId());
        route[1].push_back(defCountry->getId());
        route[2].push_back(attCountry->getNumberOfTroop() - defCountry->getNumberOfTroop() - 1);
        route[3].push_back(bonusTroops(route[1]));
        route[4].push_back(condition);
        route[5].push_back(route[3][0] - condition);
        route[6].push_back(route[2].back());
    }
    else{
        route = m_route;
        route[0].push_back(attCountry->getId());
        route[1].push_back(defCountry->getId());
        route[2].push_back(route[2].back() - defCountry->getNumberOfTroop() - 1);
        route[3].push_back(bonusTroops(route[1]));
        route[4].push_back(route[4].back() + condition);
        route[5].push_back(route[3].back() - route[4].back());
        route[6].push_back(route[2].back());
    }
    
    return route;
}

void AttackRouteCalculation::addRoute (std::shared_ptr<state::Country> attCountry, std::shared_ptr<state::Country> defCountry){
#ifdef DEBUG
    std::cout << "AttackRouteCalculation : " << __func__ << std::endl;
#endif
    if(!Computation::isCountryInList(defCountry, countriesList)){
        if(engine::AttackComputer::victoryProba(attCountry->getNumberOfTroop()-1, defCountry->getNumberOfTroop())*100 > SAFE)
            newRouteList.push_back(createRoute(attCountry, defCountry, 0));
        else if(engine::AttackComputer::victoryProba(attCountry->getNumberOfTroop()-1, defCountry->getNumberOfTroop())*100 > PASS)
            newRouteList.push_back(createRoute(attCountry, defCountry, 1));
    }
#ifdef DEBUG
    cout << "fin de " << __func__ << endl;
#endif 
}

int AttackRouteCalculation::initRouteList (){
#ifdef DEBUG
    std::cout << "AttackRouteCalculation : " << __func__ << std::endl;
#endif
    for(auto c1 : countriesList){
        int n = c1->getNumberOfTroop();
        if(n > 2){
            std::vector<std::shared_ptr<state::Country>> l = Computation::adjacentCountries(state, c1);
            for(auto c2 : l){
                addRoute(c1, c2);
            }
        }
        else continue;
    }
#ifdef DEBUG
    cout << "fin de " << __func__ << endl;
#endif
    return 1;
}

bool AttackRouteCalculation::isCountryInRoute (std::shared_ptr<state::Country> country, std::vector<std::vector<int>> route){
#ifdef DEBUG
    std::cout << "AttackRouteCalculation : " << __func__ << std::endl;
#endif
    for(auto c : route[1]){
        if(country->getId() == c)
            return true;
    }
    return false;
}

void AttackRouteCalculation::extendRoute (std::shared_ptr<state::Country> attCountry, std::shared_ptr<state::Country> defCountry,
                                          int numTroop, std::vector<std::vector<int>> route){
#ifdef DEBUG
    std::cout << "AttackRouteCalculation : " << __func__ << std::endl;
#endif
    if(!Computation::isCountryInList(defCountry, countriesList) && !isCountryInRoute(defCountry, route)){
        if(engine::AttackComputer::victoryProba(numTroop-1, defCountry->getNumberOfTroop())*100 > SAFE){
            newRouteList.push_back(createRoute(attCountry, defCountry, 0, route));
        }
        else if(engine::AttackComputer::victoryProba(numTroop-1, defCountry->getNumberOfTroop())*100 > PASS){
            newRouteList.push_back(createRoute(attCountry, defCountry, 1, route));
        }
    }
}

int AttackRouteCalculation::updateRoute(std::vector<std::vector<int>> route){
#ifdef DEBUG
    std::cout << "AttackRouteCalculation : " << __func__ << std::endl;
#endif
    int numTroop = route[2].back();
    if(numTroop < 3) return -1;
    std::shared_ptr<state::Country> c1 = totalCountriesList[route[0].back()],
                                    c2 = totalCountriesList[route[1].back()];
    for(auto c : Computation::adjacentCountries(state, c1)){
        route[6].pop_back();
        route[6].push_back(0);
        extendRoute(c1, c, numTroop, route);
    }
    for(auto c : Computation::adjacentCountries(state, c2)){
        route[6].pop_back();
        route[6].push_back(numTroop-1);
        extendRoute(c2, c, numTroop, route);
    } 
    return 1;
}

void AttackRouteCalculation::clearRouteList(){
#ifdef DEBUG
    std::cout << "AttackRouteCalculation : " << __func__ << std::endl;
#endif
    for(auto route : newRouteList)
        totalRouteList.push_back(route);
    oldRouteList.swap(newRouteList);
    newRouteList.clear();
}

int AttackRouteCalculation::updateRouteList (){
#ifdef DEBUG
    std::cout << "AttackRouteCalculation : " << __func__ << std::endl;
#endif
    int status = -1;
    clearRouteList();
    for(auto route : oldRouteList){
        int n = updateRoute(route);
        status = max(status, n);
    }
#ifdef DEBUG
    cout << "fin de " << __func__ << endl;
#endif
    return status;
}

int AttackRouteCalculation::bonusTroops (std::vector<int> conquerCountries){
    int numberBonusTroop(3);

    std::vector<int> r_presence(6,0);
    for(auto country : countriesList)
    {
        int countryId = country->getId();
        if(countryId < 9)
            r_presence[0] += 1;
        else if (countryId < 13)
            r_presence[1] += 1;
        else if (countryId < 19)
            r_presence[2]+= 1;
        else if (countryId < 26)
            r_presence[3] += 1;
        else if (countryId < 38)
            r_presence[4] += 1;
        else 
            r_presence[5] +=1;
    }

    for(auto num : conquerCountries){
        if(num < 9)
            r_presence[0] += 1;
        else if (num < 13)
            r_presence[1] += 1;
        else if (num < 19)
            r_presence[2]+= 1;
        else if (num < 26)
            r_presence[3] += 1;
        else if (num < 38)
            r_presence[4] += 1;
        else 
            r_presence[5] +=1;
    }

    if(countriesList.size() / 3 > 3){
        numberBonusTroop += (countriesList.size() / 3 - 3);
    }

    // Ajout des troupes bonus
    if (r_presence[0] == 9) numberBonusTroop += 5;
    if (r_presence[1] == 4) numberBonusTroop += 2;
    if (r_presence[2] == 6) numberBonusTroop += 3;
    if (r_presence[3] == 7) numberBonusTroop += 5;
    if (r_presence[4] == 12) numberBonusTroop += 7;
    if (r_presence[5] == 4) numberBonusTroop += 2;

    return numberBonusTroop;
}

void AttackRouteCalculation::clearRoute (){
    totalRouteList.clear();
    oldRouteList.clear();
    newRouteList.clear();
}

std::vector<std::vector<int>> AttackRouteCalculation::execute (){
#ifdef DEBUG
    std::cout << "AttackRouteCalculation : " << __func__ << std::endl;
#endif
    this->clearRoute();
    int init = initRouteList();
    if(init == -1) return {};

    while(1) {
        int update = updateRouteList();
        if(update == -1) break;
    }
    clearRouteList();
    cout << "routelist size" << totalRouteList.size() << endl;
    if(totalRouteList.empty()) return {};

    auto attackRouteCmp = [](std::vector<std::vector<int>>& a, std::vector<std::vector<int>>& b) {
        return a[5].back() > b[5].back();
    };

    std::sort(totalRouteList.begin(), totalRouteList.end(), attackRouteCmp);
#ifdef DEBUG
    for(auto route : totalRouteList)
        cout << route[5].back() << endl;
#endif
    return totalRouteList[0];
}

}