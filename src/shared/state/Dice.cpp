#include "Dice.h"
#include <chrono>
#include <iostream>

namespace state{

Dice::Dice () {

}

Dice::~Dice () {

}

Dice::Dice(int left, int right){
    std::uniform_int_distribution<int> m_distrib{left, right};
    distrib = m_distrib;
}

int Dice::thrown () {
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    
    for(int i = 0; i < 30; i++){
        distrib(re);
    }
    return distrib(re);
}

}