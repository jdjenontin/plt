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
            #ifdef DEBUG
                std::cout << "SOLO : " << __func__ << std::endl;
            #endif
            troop[0] = 1;
            troop[1] = 1;
        }
        else if (attackType == DOUBLE) {
            #ifdef DEBUG
                std::cout << "DOUBLE : " << __func__ << std::endl;
            #endif
            troop[0] = min(2, attackCountry->getNumberOfTroop()-1);
            troop[1] = min(2, defCountry->getNumberOfTroop());
        }
        else{
            #ifdef DEBUG
                std::cout << "MULTI : " << __func__ << std::endl;
            #endif
            troop[0] = attackCountry->getNumberOfTroop()-1;
            troop[1] = defCountry->getNumberOfTroop();
        }
        return troop;
    }

    // TO-DO : Verify if the ownership condition is necessary here/is checked in the render
    // TO-DO : Can be improved
    bool Attack::ableToAttack () {
        bool isOwner = attackCountry->getOwnerId() == player->getId();
        bool isntOwnerOfDef = defCountry->getOwnerId() != player->getId();

        bool adjacent = attackCountry->isAdjacent(defCountry->getId());

        bool haveTroop = attackCountry->getNumberOfTroop() > 1;
        

        return adjacent & haveTroop & isOwner & isntOwnerOfDef;
    }

    void Attack::updateState(map<string,int> attackSummary )
    {
        cout << "Begin updateState" << endl;
        attackCountry->reduceTroop(attackSummary["attackerLoos"]);
        defCountry->reduceTroop(attackSummary["defenderLoos"]);

        if(attackSummary["win"])
        {
            cout << "In updateState " << "1" << endl;
            
            int defPlayerId = defCountry->getOwnerId();
            cout << "playerId" << defPlayerId << endl;
            cout << state->getPlayersList().size() <<endl;
            shared_ptr<state::Player> defPlayer = state->getPlayersList()[defPlayerId];
            cout << "In updateState " << "2" << endl;
            defPlayer->print();
            
            defPlayer->deleteCountry(defCountry);
            
            player->addCountry(defCountry);
            cout << defCountry << endl;
            this->moveTroop();
            cout << defCountry << endl;
        }
        cout << "In updateState end" << endl;
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

    void Attack::setAttackType(engine::AttackType a_attackType){
        attackType = a_attackType;
    }
    
}

