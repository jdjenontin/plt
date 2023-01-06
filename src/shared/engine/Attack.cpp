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

    // TO-DO : Verify if the ownership condition is necessary here/is checked in the render
    bool Attack::ableToAttack () {
        bool isOwner = attackCountry->getOwnerId() == player->getId();
        bool isntOwner = defCountry->getOwnerId() != player->getId();

        bool adjacent = attackCountry->isAdjacent(defCountry->getId());
        bool haveTroop = attackCountry->getNumberOfTroop() > 1;

        return adjacent & haveTroop & isOwner & isntOwner;
    }

    void Attack::updateState(map<string,int> attackSummary )
    {
        cout << "In updateState" << endl;
        attackCountry->reduceTroop(attackSummary["attackerLoos"]);
        defCountry->reduceTroop(attackSummary["defenderLoos"]);

        if(attackSummary["win"])
        {
            cout << "In updateState" << "1" << endl;
            
            int defPlayerId = defCountry->getOwnerId();
            cout << "playerId" << defPlayerId << endl;
            cout << state->getPlayersList().size() <<endl;
            shared_ptr<state::Player> defPlayer = state->getPlayersList()[defPlayerId];
            cout << "In updateState" << "2" << endl;
            defPlayer->print();
            defPlayer->deleteCountry(defCountry);
            player->addCountry(defCountry);
            this->moveTroop();
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
        std::cout << "In attack Execute" << "\n";
        if(attackCountry->getNumberOfTroop()>2){
            int nAtt = attackCountry->getNumberOfTroop()-1;
            int nDef = defCountry->getNumberOfTroop();
            std::cout << "nAtt" << nAtt << "nDef" << nDef << "\n";
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
    
}

