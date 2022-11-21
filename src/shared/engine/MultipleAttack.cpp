#include "MultipleAttack.h"


namespace engine {

    MultipleAttack::MultipleAttack() {

    }

    MultipleAttack::MultipleAttack (Attack attack) {
        this->attackCountry = attack.attackCountry;
        this->defCountry = attack.defCountry;
        this->canAttack = attack.canAttack;
        this->attackType = attack.attackType;
    }

    MultipleAttack::MultipleAttack(bool attackType) {

    }

    MultipleAttack::~MultipleAttack() {

    }


    int MultipleAttack::execute (){

    }

}