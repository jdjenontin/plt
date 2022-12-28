#include <iostream>
#include <random>
#include <chrono>
#include <iterator>
#include <algorithm>
#include <chrono>
#include <deque>
#include "Calculation.h"
#include "Player.h"

namespace state{

Calculation::Calculation () {

}

Calculation::~Calculation () {

}

/*
* Generate a shuffle list containing a list of integer for 0 to numberOfElement
*/
std::vector<int> Calculation::shuffledTab(int numberOfElement){
    std::vector<int> temp_list;
    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    for(int i = 0; i != numberOfElement; i++){
        temp_list.push_back(i);
    }

    auto rng = std::default_random_engine(seed);
    std::shuffle(begin(temp_list), end(temp_list), rng);

    return temp_list;
}


/**
 * @brief Check if a country is the list
 * @param a_country The country to check
 * @param a_listCountry The list to check in
 * @return true if the country is in the list, false if not
*/
bool Calculation::isCountryInList (std::shared_ptr<Country>& a_country, std::vector<std::shared_ptr<Country>>& a_listCountry){
    for(auto country : a_listCountry){
        if(country->getId() == a_country->getId())
        {
            return true;
        }
    }
    return false;
}


/**
 * @brief Check if a depCountry is conected to destCountry
 * @param depCountry Depature country 
 * @param destCounty Destination country
 * @return true if both countries are connected
*/

bool Calculation::areConnected (std::shared_ptr<Player>& player, std::shared_ptr<Country>& depCountry, std::shared_ptr<Country>& destCountry)
{
    std::vector<std::shared_ptr<Country>> playerCountry = player->getCountriesList();
    std::vector<std::shared_ptr<Country>> visited;
    
    std::deque<std::shared_ptr<Country>> node_que;
    node_que.push_back(depCountry);
    std::shared_ptr<Country> node;


    // Detect the country accessible from m_country
    while(!node_que.empty())
    {
        node = node_que.front();
        node_que.pop_front();

        if(!Calculation::isCountryInList(node, visited)){
            visited.push_back(node);

            std::vector<std::shared_ptr<Country>> unvisited;

            for(auto country : playerCountry){
                if(!Calculation::isCountryInList(country, visited) && country->isAdjacent(node->getId()))
                    unvisited.push_back(country);
            }

            for(auto country : unvisited){
                node_que.push_back(country);
            }
        }
    }

    return Calculation::isCountryInList(destCountry, visited);
}

}