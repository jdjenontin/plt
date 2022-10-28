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

void Calculation::compute (Country &attacker, Country &defender) {
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

int Calculation::attack (Country &attacker, Country &defender) {
    Dice dice(1,6);
    int att, def;
    int count = 1;

    init_lostroop();

    att = attacker.getNumberTroop() - 1;

    std::cout << "attacker forces :"<< att << std::endl;

    def = defender.getNumberTroop();

    std::cout << "defender forces :"<< def << std::endl;

    while(1){
        std::cout << "turn :" << count << std::endl;

        int x = dice.thrown();

        std::cout << "attacker's dice number :"<< x << std::endl;

        int y = dice.thrown();

        std::cout << "defender's dice number :"<< y << std::endl;

        if(x >= y){
            std::cout << "attwin" << std::endl;
            def -= 1;
            lostTroopDefender += 1;
            if (def == 0) {
                std::cout << "you win the attack" << std::endl;
                attacker.reduceNumberTroop(lostTroopAttacker + 1);
                std::cout << "you have "<< attacker.getNumberTroop() << " troop now"<< std::endl;
                defender.setNumberTroop(1);
                return 0;
            }
        }
        else {
            std::cout << "defwin" << std::endl;
            att -= 1;
            lostTroopAttacker += 1;
            if (att == 0) {
                attacker.setNumberTroop(1);
                defender.reduceNumberTroop(lostTroopDefender);
                return 1;
            }
        }
        count++;
    }
}


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