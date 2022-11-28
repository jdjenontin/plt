#include "Attack.h"

#include <iostream>
#include <random>
#include <chrono>
#include <iterator>
#include <algorithm>
#include <chrono>
#include <vector>


using namespace state;
using namespace std;

namespace engine {


Attack::Attack() {
    Dice dice(1,6);
    this->attackCountry = attackCountry;
    this->defCountry = defCountry;
    this->canAttack = canAttack;
    this->attackType = attackType;
    this->dice6 = dice;
}

Attack::Attack(bool attackType) {
    this->attackType = attackType;
    
}

Attack::~Attack() {

}

void Attack::movetroop () {
    int s = attackCountry->getNumberTroop();
    if(s > 1){
        defCountry->addNumberTroop(1);
        attackCountry->reduceNumberTroop(1);
    }
    else{
        player->winAttack = false;
    }
}

bool Attack::existAttackCountry () {
    return player->existCountry(*attackCountry);
}

bool Attack::existDefCountry () {
    return player->existCountry(*defCountry);
}

bool Attack::abletoattack () {
    this->canAttack = attackCountry->getNumberTroop() > 1;
    return attackCountry->getNumberTroop() > 1;
}

bool Attack::isadjacent () {
    return attackCountry->isAdjacent(defCountry->getNumberCountry());
}

int Attack::execute (int maxAtt, int maxDef, int minAtt, int minDef) {
    //Comparing max die to see who wins 
    if(maxAtt > maxDef)
    {
        std::cout << "Attacker wins!" << std::endl;
        defCountry->reduceNumberTroop(1);
        if (defCountry->getNumberTroop() == 0) 
        {
            std::cout << "Successful attack!" << std::endl;
            attackCountry->reduceNumberTroop(1);
            std::cout << "You have "<< attackCountry->getNumberTroop() << " troop now"<< std::endl;
            defCountry->setNumberTroop(1);

            state::Player* p = state->belongsto(defCountry);
            p->deleteCountry(defCountry);
            player->addCountry(defCountry);
            player->winAttack = true;
            canAttack = 0;

            return 1;
        }

    }

    else if (maxDef >= maxAtt)
    {
        std::cout << "Defender wins!" << std::endl;
        attackCountry->reduceNumberTroop(1);
        if (attackCountry->getNumberTroop() == 1)  //If the attacking country only has one troop, the attack is a failure
        {
            attackCountry->setNumberTroop(1);
            defCountry->reduceNumberTroop(1);
            canAttack = 0;
            std::cout << "Failed attack!" << std::endl;
            return 0;
        }
    }

    //Comparing min die to see who wins 
    if (minAtt > minDef)
    {
        std::cout << "Attacker wins!" << std::endl;
        defCountry->reduceNumberTroop(1);
        if (defCountry->getNumberTroop() == 0) 
        {
            std::cout << "Successful attack!" << std::endl;
            attackCountry->reduceNumberTroop(1);
            std::cout << "You have "<< attackCountry->getNumberTroop() << " troop now"<< std::endl;
            defCountry->setNumberTroop(1);

            state::Player* p = state->belongsto(defCountry);
            p->deleteCountry(defCountry);
            player->addCountry(defCountry);
            player->winAttack = true;
            canAttack = 0;

            return 1;
        }
        return 0;
    }

    else if (minDef >= minAtt)
    {
        std::cout << "Defender wins!" << std::endl;
        attackCountry->reduceNumberTroop(1);
        if (attackCountry->getNumberTroop() == 1) 
        {
            attackCountry->setNumberTroop(1);
            defCountry->reduceNumberTroop(1);
            canAttack = 0;
            std::cout << "Failed attack!" << std::endl;
            return 0;
        }
        return 0;
    }

    return 0;
}

//Different attack types
int Attack::soloAttack(){

    int att, def;
    int maxAtt, maxDef = 0;
    int diceAtt = 0;

    att = attackCountry->getNumberTroop();

    std::cout << "attacker forces :"<< att << std::endl;

    def = defCountry->getNumberTroop();

    std::cout << "defender forces :"<< def << std::endl;


    //Generating dice for the attacker
    diceAtt = dice6.thrown();
    maxAtt = diceAtt;
    std::cout << "attacker's die numbers :"<< diceAtt << std::endl;

    //Generating die for the defender
    maxDef = dice6.thrown();   
    std::cout << "defender's dice number :"<< maxDef << std::endl;

    //Comparing die to see who wins 
    if(maxAtt > maxDef){
        //Attacker wins
        std::cout << "Attacker wins!" << std::endl;
        def -= 1;
        defCountry->reduceNumberTroop(1);
        if (defCountry->getNumberTroop() == 0) {
            std::cout << "Successful attack!" << std::endl;
            attackCountry->reduceNumberTroop(1);
            std::cout << "You have "<< attackCountry->getNumberTroop() << " troop now"<< std::endl;
            defCountry->setNumberTroop(1);

            state::Player* p = state->belongsto(defCountry);
            p->deleteCountry(defCountry);
            player->addCountry(defCountry);
            player->winAttack = true;

            return 1;
        }
        return 0;
    }

    else{
        //Defender wins
        std::cout << "Defender wins!" << std::endl;
        att -= 1;
        attackCountry->reduceNumberTroop(1);
        if (attackCountry->getNumberTroop() == 1) {
            attackCountry->setNumberTroop(1);
            canAttack = 0;
            std::cout << "Failed attack!" << std::endl;

            return 0;
        }
        return 0;
    }

}

int Attack::doubleAttack(){

    int att, def;
    int numberDieDef, maxAtt1, maxAtt2, maxDef1, maxDef2, maxAtt, minAtt, maxDeff, minDeff = 0;



    att = attackCountry->getNumberTroop();
    std::cout << "attacker forces :"<< att << std::endl;

    def = defCountry->getNumberTroop();
    numberDieDef = def;
    std::cout << "defender forces :"<< def << std::endl;

    //Generating die for the attacker
    int diceAtt1 = dice6.thrown();
    int diceAtt2 = dice6.thrown();
    maxAtt1 = diceAtt1;
    maxAtt2 = diceAtt2;
    std::cout << "attacker's die numbers :"<< diceAtt1 << "\t" << diceAtt2 << std::endl;
    vector<int> allAttackDie = {diceAtt1, diceAtt2};


    //Generating die for the defender
    if (numberDieDef == 2)
    {
        maxDef1 = dice6.thrown();
        maxDef2 = dice6.thrown();
        maxDeff = std::max(maxDef1, maxDef2);
        minDeff = std::min(maxAtt1, maxDef2);
        std::cout << "defender's dice number :"<< maxDef1 << "\t" << maxDef2 << std::endl;
    } 

    else 
    {
        maxDeff = dice6.thrown();   
        std::cout << "defender's dice number :"<< maxDef1 << std::endl;
    }

    maxAtt = std::max(maxAtt1, maxAtt2);
    minAtt = std::min(maxAtt1, maxAtt2);

    return execute(maxAtt, maxDeff, minAtt, minDeff);
}

int Attack::tripleAttack(){


    int att, def;
    int numberDieDef, maxAtt1, maxAtt2, maxDef1, maxDef2, maxAtt, minAtt, maxDeff, minDeff = 0;




    att = attackCountry->getNumberTroop();
    std::cout << "attacker forces :"<< att << std::endl;

    def = defCountry->getNumberTroop();

    if (def > 1){
        numberDieDef = 2;
    }

    else numberDieDef = 1;
    std::cout << "defender forces :"<< def << std::endl;

    //Generating die for the attacker
    int diceAtt1 = dice6.thrown();
    int diceAtt2 = dice6.thrown();
    int diceAtt3 = dice6.thrown();
    
    maxAtt1 = std::max(diceAtt1, diceAtt2);
    maxAtt2 = std::max(std::min(diceAtt1, diceAtt2), diceAtt3);
    std::cout << "attacker's die numbers :"<< diceAtt1 << "\t" << diceAtt2 << "\t" << diceAtt3 << std::endl;


    //Generating die for the defender
    if (numberDieDef == 2)
    {
        maxDef1 = dice6.thrown();
        maxDef2 = dice6.thrown();
        maxDeff = std::max(maxDef1, maxDef2);
        minDeff = std::min(maxAtt1, maxDef2);
        std::cout << "defender's dice number :"<< maxDef1 << "\t" << maxDef2 << std::endl;
    } 

    else 
    {
        maxDeff = dice6.thrown();   

        std::cout << "defender's dice number :"<< maxDef1 << std::endl;
    }

    maxAtt = std::max(maxAtt1, maxAtt2);
    minAtt = std::min(maxAtt1, maxAtt2);

    return execute(maxAtt, maxDeff, minAtt, minDeff);
}

int Attack::multipleAttack(){
    //Tant qu'on peux attaquer, on attaque avec le nombre maximum de troupes
    while(canAttack){
        int numAtt = 0;
        if(attackCountry->getNumberTroop() > 3){
            numAtt = tripleAttack();
        }

        else if(attackCountry->getNumberTroop() == 3){
            numAtt = doubleAttack();
        }

        else if(attackCountry->getNumberTroop() == 2){
            numAtt = soloAttack();
        }
        
    }
    return 1;
}


//Getters Setters
void Attack::setAttackCountry (state::Country* attackCountry){
    this->attackCountry = attackCountry;
    this->canAttack = 1;

}

state::Country* Attack::getAttackCountry (){
    return attackCountry;
}

void Attack::setDefCountry (state::Country* defCountry){
    this->defCountry = defCountry;
}


state::Country* Attack::getDefCountry (){
    return defCountry;
}

}

