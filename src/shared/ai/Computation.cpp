#include "Computation.h"
#include <iostream>

using namespace state;

namespace ai{

    /**
     * Get the adjacentCountries of a specific country
     * @param state The current state
     * @param a_country The country 
     * @return List of the countries
    */
    std::vector<state::Country*> Computation::adjacentCountries (State* state, state::Country* a_country)
    {
        std::vector<state::Country*>  adajcents;

        std::vector<state::Country*> allCountries = state->getListCountires();

        for(int i=0; i<42;i++) {
            if (a_country->isAdjacent(i)) {
                std::cout << "The AI can attack " << allCountries.at(i)->getNameCountry() << ". \n";
                adajcents.push_back(allCountries.at(i));
            }
        }

        return adajcents;
    }

    /**
     * @brief Check if a country is the list
     * @param a_country The country to check
     * @param a_listCountry The list to check in
     * @return true if the country is in the list, false if not
    */
    bool Computation::isCountryInList (state::Country* a_country, std::vector<Country*> a_listCountry){
        for(auto country : a_listCountry){
            std::cout << country->getNumberCountry() << a_country->getNumberCountry() << std::endl;
            if(country->getNumberCountry() == a_country->getNumberCountry())
            {
                return true;
            }
        }
        return false;
    }
}