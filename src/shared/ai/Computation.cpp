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
    std::vector<std::shared_ptr<state::Country>> Computation::adjacentCountries (std::shared_ptr<state::State>& state, std::shared_ptr<state::Country> a_country)
    {
        std::vector<std::shared_ptr<Country>> adajcents;

        std::vector<std::shared_ptr<Country>> allCountries = state->getCountriesList();

        for(int i=0; i<42;i++) {
            if (a_country->isAdjacent(i)) {
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
    bool Computation::isCountryInList (std::shared_ptr<state::Country>& a_country, std::vector<std::shared_ptr<state::Country>>& a_listCountry){
        for(auto country : a_listCountry){
    #ifdef DEBUG
            std::cout << country->getId() << a_country->getId() << std::endl;
    #endif
            if(country->getId() == a_country->getId())
            {
                return true;
            }
        }
        return false;
    }

}