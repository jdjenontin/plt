#include "NormalAi.h"
#include <iostream>
#include <algorithm>

using namespace state;

namespace ai{
    NormalAi::NormalAi(){

    }

    NormalAi::~NormalAi(){

    }

    int NormalAi::place(){
        std::vector<int> nbOfCountryC = {9,4,6,7,12,4};
        std::vector<int> ai_presence =  this->presenceOnContinents();

        std::vector<int> unOwnedCountries(6,0);

        std::transform(nbOfCountryC.begin(), nbOfCountryC.end(), ai_presence.begin(), 
                        unOwnedCountries.begin(), [](int a, int b) { return a - b; });

        return 0;

    }
    
};