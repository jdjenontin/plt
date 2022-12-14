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
 * @brief Detect if the m_country is in the list of player
*/
bool Reinforce::existM_country () {
    return player->existCountry(*m_country);
}

/**
 * @brief Detect if the n_country is in the list of player
*/
bool Reinforce::existN_country () {
    return player->existCountry(*n_country);
}

/**
 * @brief Check if a n_country is connected to n_country and add troop if yes
*/
void Reinforce::execute(){

    bool connected = state::Calculation::areConnected(player, m_country, n_country);
        
    // Add a troop
    
    if(connected){
        if(m_country -> getNumberTroop() > 1){
            n_country -> addNumberTroop(1);
            m_country -> reduceNumberTroop(1);
        }       
    }

}
}