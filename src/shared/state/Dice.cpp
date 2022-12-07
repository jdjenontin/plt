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
    if(m_left <= m_right &&  m_right > -1)
    {
        return m_left + (rand()%(m_right-m_left+1));
    }
    else
    {
        std::cerr << "Dice error : You tried to throw dice between " << m_left << " and " << m_right << std::endl;
        return 0;
    }
        
}

/**
 * @brief Creat a dice
 * @param left The minimum value the dice can tahe
 * @param right The max value ethe dice can return
*/
void Dice::updateDice(int a_left, int a_right){
    m_left = a_left;
    m_right = a_right;
}

}