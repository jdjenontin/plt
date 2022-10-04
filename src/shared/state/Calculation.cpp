#include <iostream>
#include <random>
#include <chrono>

#include "Calculation.h"

namespace state{

Calculation::Calculation () {

}

Calculation::~Calculation () {

}

void Calculation::compute (Country country1, Country country2) {

}

int Calculation::throwdice () {
    int valeur;
    srand((unsigned int) time(0));

    return valeur = rand()%6 + 1;
}

void Calculation::init_lostroop () {
    lostTroopAttacker = 0;
    lostTroopDefender = 0;
}

int Calculation::attack (Country attacker, Country defender) {
    int att, def;

    init_lostroop();

    att = attacker.getNumberTroop() - 1;

    std::cout << "number :"<< att << std::endl;

    def = defender.getNumberTroop();

    std::cout << "number :"<< def << std::endl;

    while(1){
        int x = throwdice();

        std::cout << "number x:"<< x << std::endl;

        int y = throwdice();

        std::cout << "number y:"<< y << std::endl;

        if(x > y){
            std::cout << "attwin" << std::endl;
            def -= 1;
            lostTroopDefender += 1;
            if (def == 0) {
                attacker.reduceNumberTroop(lostTroopAttacker);
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
    }
}

}