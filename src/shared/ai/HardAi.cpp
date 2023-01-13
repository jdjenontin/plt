#include <iostream>
#include <algorithm>

#include "HardAi.h"

#define DEBUG 1;

using namespace std;
using namespace state;

namespace ai{

vector<state::Country*> playerlistcountries;

vector<int> ameriqueN(9, 0), ameriqueS(4, 0), afrique(6, 0), europe(7, 0), asie(12, 0), ocenanie(4, 0);

vector<int> p1, p2;

int bonus;

HardAi::HardAi(){

}

HardAi::HardAi(shared_ptr<State> a_state) : Ai(a_state){

}

HardAi::~HardAi(){

}

void HardAi::place(){
    
    
#ifdef DEBUG
    cout << "------------------------------------------" << endl;
#endif
}

void HardAi::attack(){

}

void HardAi::reinforce(){

}


void HardAi::execute(shared_ptr<Player> a_player){
#ifdef DEBUG
    std::cout << "Hard AI" << __func__ << std::endl;
#endif 
}

}
