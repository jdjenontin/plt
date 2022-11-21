#include "Attack.h"

namespace engine {

Attack::Attack() {
    
}

Attack::~Attack() {

}

void Attack::setc_country (state::Country* c_country){
    this->c_country = c_country;
}

void Attack::setd_country (state::Country* d_country){
    this->d_country = d_country;
}

void Attack::movetroop () {
    int s = c_country->getNumberTroop();
    if(s > 1){
        d_country->addNumberTroop(1);
        c_country->reduceNumberTroop(1);
    }
    else{
        player->winAttack = false;
    }
}

bool Attack::existC_country () {
    return player->existCountry(*c_country);
}

bool Attack::existD_country () {
    return player->existCountry(*d_country);
}

bool Attack::abletoattack () {
    return c_country->getNumberTroop() > 1;
}

bool Attack:: isadjacent () {
    return c_country->isAdjacent(d_country->getNumberCountry());
}

int Attack::execute () {
    state::Calculation calcul;
    state::Dice dice(1,6);

    calcul.compute(c_country, d_country);

    int win = calcul.attack(c_country, d_country);

    if(win == 0) {
        state::Player* p = state->belongsto(d_country);
        p->deleteCountry(d_country);
        player->addCountry(d_country);
        player->winAttack = true;
        return 1;
    }
    else return 0;
}

}