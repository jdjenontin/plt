#include "Dice.h"
#include <chrono>
#include <iostream>

namespace state{

Dice::Dice () {

}

Dice::~Dice () {

}

/**
 * @brief Creat a dice
 * @param left The minimum value the dice can tahe
 * @param right The max value ethe dice can return
*/

Dice::Dice(int left, int right){
    m_left = left;
    m_right = right;
}


/**
 * Return a random value
 * @return A random value
*/
int Dice::thrown () {
    return m_left + (rand()%m_right);
}


}