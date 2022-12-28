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
        if(country->getId() == a_country->getId())
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
void Reinforce::setM_country(const std::shared_ptr<state::Country>& m_country){
    this->m_country = m_country;
}

/**
 * @brief Set the country to reinforce
*/
void Reinforce::setN_country(const std::shared_ptr<state::Country>& m_country){
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
int Reinforce::execute(){

    bool connected = state::Calculation::areConnected(player, m_country, n_country);
        
    // Add a troop
    
    if(connected){
        if(m_country -> getNumberOfTroop() > 1){
            n_country -> addTroop(1);
            m_country -> reduceTroop(1);
        }       
    }
    else return 0;
    return 1;
}
}