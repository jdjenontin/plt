#include "Reinforce.h"
#include <deque>


namespace engine {

/**
 * @brief Check if a country is the list
 * @param a_country The country to check
 * @param a_listCountry The list to check in
 * @return true if the country is in the list, false if not
*/
bool countryInList(state::Country* a_country, std::vector<state::Country*> a_listCountry){
    for(auto country : a_listCountry){
        if(country->getNumberCountry() == a_country->getNumberCountry())
        {
            return true;
        }
    }
    return false;
}

Reinforce::Reinforce() {

}

Reinforce::~Reinforce() {

}

/**
 * @brief Set the country to perform the reinforce from
*/
void Reinforce::setm_country (state::Country* m_country){
    this->m_country = m_country;
}


/**
 * @brief Set the country to reinforce
*/
void Reinforce::setn_country (state::Country* n_country){
    this->n_country = n_country;
}


/**
 * @brief Check if a n_country is connected to n_country and add troop if yes
*/

void Reinforce::execute(){

    std::vector<state::Country *> playerCountry = player->getListCountry();
    std::vector<state::Country *> visited;
    
    std::deque<state::Country *> node_que;
    node_que.push_back(m_country);
    state::Country * node;


    // Detect the country accessible from m_country
    while(!node_que.empty())
    {
        node = node_que.front();
        node_que.pop_front();

        if(!countryInList(node, visited)){
            visited.push_back(node);

            std::vector<state::Country *> unvisited;

            for(auto country : playerCountry){
                if(!countryInList(country, visited) && country->isAdjacent(node->getNumberCountry()))
                    unvisited.push_back(country);
            }

            for(auto country : unvisited){
                node_que.push_back(country);
            }
        }
    }
        
    // Add a troop
    for(auto country : visited){
        if(country -> getNameCountry() ==  n_country -> getNameCountry()){
            if(m_country -> getNumberTroop() > 1){
                n_country -> addNumberTroop(1);
                m_country -> reduceNumberTroop(1);
            }
            
    }
}

}
}