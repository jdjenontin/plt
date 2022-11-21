#include "Attack.h"

#include <iostream>
#include <random>
#include <chrono>
#include <iterator>
#include <algorithm>
#include <chrono>

using namespace state;
using namespace std;

namespace engine {


Attack::Attack() {
    this->attackCountry = attackCountry;
    this->defCountry = defCountry;
    this->canAttack = canAttack;
    this->attackType = attackType;
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

int Attack::execute (int attackType) {
    if(attackType==1){
        return soloAttack();
    }

    else if (attackType==2){
        return doubleAttack();
    }

    else{
        return multipleAttack();
    }
}

//Different attack types
int Attack::soloAttack(){

}

int Attack::doubleAttack(){
    
}

int Attack::multipleAttack(){

    Dice dice1(1,6);
    Dice dice100(0,99);

    int att, def;
    int count = 1;
    int numberDieAtt, numberDieDef, maxAtt1, maxAtt2, maxDef1, maxDef2, maxAtt, minAtt, maxDeff, minDeff = 0;
    int diceDef1, diceDef2 = 0;
    int lostTroopAttacker = 0;
    int lostTroopDefender = 0;


    att = attackCountry->getNumberTroop();

    std::cout << "attacker forces :"<< att << std::endl;

    def = defCountry->getNumberTroop();

    if (def > 2) numberDieDef = 2;
    else numberDieDef = def;
        

    std::cout << "defender forces :"<< def << std::endl;

    while(1){
        
        if (canAttack){
            std::cout << "turn :" << count << std::endl;

            //Creating 100 values between 1 and 6
            std::vector<int> dieArray = {};
            for (int i; i < 100; i++){
                dieArray.push_back(dice1.thrown());
            }
            

            //Generating die for the attacker
            if (att > 2)
            {
                int diceAtt1 = dieArray.at(dice100.thrown());
                int diceAtt2 = dieArray.at(dice100.thrown());
                int diceAtt3 = dieArray.at(dice100.thrown());
                
                numberDieAtt = 3;
                maxAtt1 = std::max(diceAtt1, diceAtt2);
                maxAtt2 = std::max(std::min(diceAtt1, diceAtt2), diceAtt3);

                std::cout << "attacker's die numbers :"<< diceAtt1 << "\t" << diceAtt2 << "\t" << diceAtt3 << std::endl;

            }

            else if (att = 2)
            {
                int diceAtt1 = dieArray.at(dice100.thrown());
                int diceAtt2 = dieArray.at(dice100.thrown());
                numberDieAtt = 2;
                maxAtt1 = diceAtt1;
                maxAtt2 = diceAtt2;
                std::cout << "attacker's die numbers :"<< diceAtt1 << "\t" << diceAtt2 << std::endl;
                std::vector<int> allAttackDie = {diceAtt1, diceAtt2};
            }

            else if (att = 1)
            {
                int diceAtt1 = dieArray.at(dice100.thrown());
                numberDieAtt = 1;
                maxAtt1 = diceAtt1;
                std::cout << "attacker's die numbers :"<< diceAtt1 << std::endl;
                
            }

            //Generating die for the defender
            if (numberDieDef = 2)
            {
                maxDef1 = dieArray.at(dice100.thrown());
                maxDef2 = dieArray.at(dice100.thrown());
                std::cout << "defender's dice number :"<< maxDef1 << "\t" << maxDef2 << std::endl;
            } 

            else 
            {
                maxDef1 = dieArray.at(dice100.thrown());   
                std::cout << "defender's dice number :"<< maxDef1 << std::endl;
            }

            maxAtt = std::max(maxAtt1, maxAtt2);
            minAtt = std::min(maxAtt1, maxAtt2);
            maxDeff = std::max(maxDef1, maxDef2);
            minDeff = std::min(maxAtt1, maxDef2);

            //Comparing die to see who wins 
            if(maxAtt > maxDeff){
                std::cout << "Attacker wins!" << std::endl;
                def -= 1;
                lostTroopDefender += 1;
                if (def == 0) {
                    std::cout << "Successful attack!" << std::endl;
                    attackCountry->reduceNumberTroop(lostTroopAttacker + 1);
                    std::cout << "You have "<< attackCountry->getNumberTroop() << " troop now"<< std::endl;
                    defCountry->setNumberTroop(1);

                    state::Player* p = state->belongsto(defCountry);
                    p->deleteCountry(defCountry);
                    player->addCountry(defCountry);
                    player->winAttack = true;

                    return 0;
                }

                if (minAtt > minDeff)
                {
                    std::cout << "Attacker wins!" << std::endl;
                    def -= 1;
                    lostTroopDefender += 1;
                    if (def == 0) 
                    {
                        std::cout << "Successful attack!" << std::endl;
                        attackCountry->reduceNumberTroop(lostTroopAttacker + 1);
                        std::cout << "You have "<< attackCountry->getNumberTroop() << " troop now"<< std::endl;
                        defCountry->setNumberTroop(1);

                        state::Player* p = state->belongsto(defCountry);
                        p->deleteCountry(defCountry);
                        player->addCountry(defCountry);
                        player->winAttack = true;
                        return 0;
                    }
                }

                else 
                {
                    std::cout << "Defender wins!" << std::endl;
                    att -= 1;
                    lostTroopAttacker += 1;
                    if (att == 1) 
                    {
                        attackCountry->setNumberTroop(1);
                        defCountry->reduceNumberTroop(lostTroopDefender);
                        canAttack = 0;
                        std::cout << "Failed attack!" << std::endl;
                        return 1;
                    }
                }   
            }

            else{
                std::cout << "Defender wins!" << std::endl;
                att -= 1;
                lostTroopAttacker += 1;
                if (att == 1) {
                    attackCountry->setNumberTroop(1);
                    defCountry->reduceNumberTroop(lostTroopDefender);
                    canAttack = 0;
                    std::cout << "Failed attack!" << std::endl;

                    return 1;
                }
            }

            count++;
        }
        return 1;
    }
}


//Getters Setters
void Attack::setAttackCountry (state::Country* attackCountry){
    this->attackCountry = attackCountry;
    this->canAttack = 1;

}

state::Country* getAttackCountry (){

}

void Attack::setDefCountry (state::Country* defCountry){
    this->defCountry = defCountry;
}


state::Country* getDefCountry (){

}


}

