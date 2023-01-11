#include "NormalAi.h"
#include <iostream>
#include <algorithm>


using namespace std;
using namespace state;

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
}

NormalAi::NormalAi(shared_ptr<State> a_state) : Ai(a_state){
    
}

NormalAi::~NormalAi() {
    
}

void NormalAi::execute (shared_ptr<Player> a_player){
    return;
}

void NormalAi::place (){

}

void NormalAi::attack (){

}

void NormalAi::reinforce (){

}
    
};