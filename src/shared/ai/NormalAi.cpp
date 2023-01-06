#include "NormalAi.h"
#include <iostream>
#include <algorithm>


namespace ai{


    /*void NormalAi::place(){
        std::vector<int> nbOfCountryC = {9,4,6,7,12,4};
        std::vector<int> ai_presence =  this->presenceOnContinents();

        std::vector<int> unOwnedCountries(6,0);

        std::transform(nbOfCountryC.begin(), nbOfCountryC.end(), ai_presence.begin(), 
                        unOwnedCountries.begin(), [](int a, int b) { return a - b; });

        return;
    
    }*/

NormalAi::NormalAi () {
    status = state::PLAYING;
    type = state::BOT;
    difficulty = Difficulty::NORMAL;
    name = "BOT";
}

NormalAi::NormalAi(int id){
    this->id = id;
    status = state::PLAYING;
    type = state::BOT;
    difficulty = Difficulty::NORMAL;
}

NormalAi::~NormalAi() {
    
}

void NormalAi::execute (){

}

void NormalAi::place (){

}

void NormalAi::attack (){

}

void NormalAi::reinforce (){

}
    
};