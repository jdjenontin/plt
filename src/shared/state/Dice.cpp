#include "Dice.h"
#include <chrono>
#include <iostream>

namespace state{

Dice::Dice () {

}

int Dice::thrown () {
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    
    for(int i = 0; i < 20; i++){
        distrib(re);
    }
    return distrib(re);
}

}