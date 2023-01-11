#include "Attack.h"
#include <functional>
#include <iostream>
#include <algorithm>

#define DEBUG 1

using namespace state;
using namespace std;

namespace engine {

    Attack::Attack() {
        dice.updateDice(1,6);
    }

    Attack::~Attack() {

    }

    vector<int> Attack::compTroops(){
        vector<int> troop(2,0);

        if(attackType == SOLO){
            troop[0] = 1;
            troop[1] = 1;
        }
        else if (attackType == DOUBLE) {
            troop[0] = min(2, attackCountry->getNumberOfTroop()-1);
            troop[1] = min(2, defCountry->getNumberOfTroop());
        }
        else{
            troop[0] = attackCountry->getNumberOfTroop()-1;
            troop[1] = defCountry->getNumberOfTroop();
        }
<<<<<<< HEAD
=======

>>>>>>> development
        return troop;
    }

    // TO-DO : Verify if the ownership condition is necessary here/is checked in the render
    // TO-DO : Can be improve
    bool Attack::ableToAttack () {
        bool isOwner = attackCountry->getOwnerId() == player->getId();
        bool isntOwnerOfDef = defCountry->getOwnerId() != player->getId();

        bool adjacent = attackCountry->isAdjacent(defCountry->getId());

        bool haveTroop = attackCountry->getNumberOfTroop() > 1;
        

        return adjacent & haveTroop & isOwner & isntOwnerOfDef;
    }

    void Attack::updateState(map<string,int> attackSummary )
    {
        attackCountry->reduceTroop(attackSummary["attackerLoos"]);
        defCountry->reduceTroop(attackSummary["defenderLoos"]);

        if(attackSummary["win"])
        {
            int defPlayerId = defCountry->getOwnerId();
            shared_ptr<state::Player> defPlayer = state->getPlayersList()[defPlayerId];
            defPlayer->deleteCountry(defCountry);
            player->addCountry(defCountry);
            this->moveTroop();
        }
    }

    void Attack::moveTroop () {
        int s = attackCountry->getNumberOfTroop();
        if(s > 1){
            defCountry->addTroop(1);
            attackCountry->reduceTroop(1);
        }
    }

    int Attack::execute()
    {
    #ifdef DEBUG
        std::cout << "function : " << __func__ << std::endl;
    #endif
        if(this->ableToAttack()){
            vector<int> troops = this->compTroops();
            int nAtt = troops[0];
            int nDef = troops[1];
            map<string,int> attackSummary = AttackComputer::attackNvM(nAtt, nDef);
            this->updateState(attackSummary);
            return 1;
        }
        else
        {
            cout << "Attack impossible" << endl;
            return 0;
        }
        
    }

    bool Attack::isAdjacent()
    {
        return attackCountry->isAdjacent(defCountry->getId());
    }

    //Getters Setters
    void Attack::setAttackCountry(const std::shared_ptr<state::Country>& attackCountry){
        this->attackCountry = attackCountry;
    }

    const std::shared_ptr<state::Country>& Attack::getAttackCountry() const{
        return attackCountry;
    }

    void Attack::setDefCountry(const std::shared_ptr<state::Country>& defCountry){
        this->defCountry = defCountry;
    }

    const std::shared_ptr<state::Country>& Attack::getDefCountry() const{
        return defCountry;
    }

    const std::map<std::string,int>& Attack::getAttSummary() const{
        return attSummary;
    }

    void setAttackType(engine::AttackType attackType){
        attackType = attackType;
    }
    
}

