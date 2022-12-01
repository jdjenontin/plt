#include <iostream>
#include <random>
#include <chrono>
#include <iterator>
#include <algorithm>
#include <chrono>

#include "Calculation.h"

namespace state{

Calculation::Calculation () {

}

Calculation::~Calculation () {

}

void Calculation::compute (Country* attacker, Country* defender) {
    std::cout << "your win rate is :(its not available now)" << std::endl;
}

int Calculation::throwdice () {
    srand(time(0));
    std::cout << rand() << std::endl;
    return (rand() % 6 + 1);
}

void Calculation::init_lostroop () {
    lostTroopAttacker = 0;
    lostTroopDefender = 0;
}
/*
int Calculation::attack (Country* attacker, Country* defender, bool canAttack) {
        return 0;
    }*/


/*
* Generate a shuffle list containing a list of integer for 0 to numberOfElement
*/
std::vector<int> Calculation::shuffledTab(int numberOfElement){
    std::vector<int> temp_list;
    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    for(int i = 0; i != numberOfElement; i++){
        temp_list.push_back(i);
    }

    auto rng = std::default_random_engine(seed);
    std::shuffle(begin(temp_list), end(temp_list), rng);

    return temp_list;
}

}