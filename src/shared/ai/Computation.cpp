#include "Computation.h"
#include <iostream>

using namespace state;

//#define DEBUG 1

namespace ai{

    /**
     * Get the adjacentCountries of a specific country
     * @param state The current state
     * @param a_country The country 
     * @return List of the countries
    */
    std::vector<std::shared_ptr<state::Country>> Computation::adjacentCountries (const std::shared_ptr<state::State>& state, const std::shared_ptr<state::Country> a_country)
    {
        std::vector<std::shared_ptr<Country>> adajcents;

        std::vector<std::shared_ptr<Country>> allCountries = state->getCountriesList();
        #ifdef DEBUG
            std::cout << __func__ << std::endl;
            for(auto i : a_country->getAdjacentCountries()) {
                std::cout << i << std::endl;
            } 
        #endif

        for(auto i : a_country->getAdjacentCountries()) {
            adajcents.push_back(allCountries.at(i));
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

    double Computation::borderSecurityRatio (const std::shared_ptr<state::State>& a_state,const std::shared_ptr<state::Country>& a_country)
    {
        #ifdef DEBUG
            std::cout << __func__ << std::endl;
        #endif
        std::vector<std::shared_ptr<Country>> adajcents = Computation::adjacentCountries(a_state, a_country);

        double bst = 0;

        for(auto& country : adajcents){
            if(country->getOwnerId() != a_country->getOwnerId())
                bst += country->getNumberOfTroop();
        }
        #ifdef DEBUG
            std::cout << "bst : " << bst<< std::endl;
        #endif
        double bsr = bst/a_country->getNumberOfTroop();

        return bsr;

    }


}