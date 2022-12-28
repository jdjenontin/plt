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

    int Attack::attackSimple(int nAttacker, int nDefender) {
        if (nAttacker > 3 || nDefender > 2){
            cerr << __FUNCTION__ <<" n'est valide que pour nAttacker > 3 et nDefender > 2)" << endl;
            exit(1);
        }

        vector <int> attDices(nAttacker, 0);
        vector <int> defDices(nDefender, 0);

        generate(attDices.begin(), attDices.end(), bind(&Dice::thrown, &dice));
        generate(defDices.begin(), defDices.end(), bind(&Dice::thrown, &dice));

        sort(attDices.begin(), attDices.end(), greater<int>());
        sort(defDices.begin(), defDices.end(), greater<int>());

        int nDices = min(attDices.size(), defDices.size());

        int defenderLoss = 0;

        for(int i = 0; i < nDices; i++)
        {
            if(attDices[i] > defDices[i])
            {
                defenderLoss++;
            }
        }

        return defenderLoss;
    }

    // TO-DO : Can be optimized 
    map<string,int> Attack::attackNvM(int nAttacker, int nDefender)
    {
        if(DEBUG)
        {
            cout << "---------------------------" << endl;
            cout << __FUNCTION__ << endl;
            cout << "Number of att : " << nAttacker << endl;
            cout << "Number of def : " << nDefender << endl;
        }

        map<string,int> attackSummary;

        int defenderLoos(0), attackerLoos(0), defLoos(0), nDices(0);
        
        while((nAttacker > 0) & (nDefender > 0)){
            if((nAttacker <= 3) & (nDefender <= 2)){
                nDices = min(nAttacker, nDefender);
                defLoos = attackSimple(nAttacker, nDefender);
            }
            else if((nAttacker > 3) & (nDefender <= 2)){
                nDices = min(nAttacker, nDefender);
                defLoos = attackSimple(3, nDefender);
            }
            else if((nAttacker <= 3 )& (nDefender > 2)){
                nDices = min(nAttacker, nDefender);
                defLoos = attackSimple(nAttacker, 2);
            }
            else{
                nDices = 2;
                defLoos = attackSimple(3, 2);
            }
            
            nDefender -= defLoos;
            defenderLoos += defLoos;

            nAttacker -= (nDices-defLoos);
            attackerLoos += (nDices - defLoos);
        }

        // Attack summary 
        attackSummary["win"] = (int)(nDefender == 0);
        attackSummary["attackerLoos"] = attackerLoos;
        attackSummary["defenderLoos"] = defenderLoos;

        if(DEBUG)
        {
            cout << "## Summary" << endl;
            for (auto it = attackSummary.begin(); it != attackSummary.end(); it++) {
                cout << it->first << ": " << it->second << endl;
            }
        }

        return attackSummary;
    }

    // TO-DO : Verify if the ownership condition is necessary here/is checked in the render
    bool Attack::ableToAttack () {
        bool isOwner = attackCountry->getOwnerId() == player->getId();
        bool isntOwner = defCountry->getOwnerId() == player->getId();

        bool adjacent = attackCountry->isAdjacent(defCountry->getId());
        bool haveTroop = attackCountry->getNumberOfTroop() > 1;

        return adjacent & haveTroop & isOwner & isntOwner;
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

    void Attack::execute()
    {
        if(this->ableToAttack()){
            int nAtt = attackCountry->getNumberOfTroop()-1;
            int nDef = defCountry->getNumberOfTroop();
            map<string,int> attackSummary = this->attackNvM(nAtt, nDef);
            this->updateState(attackSummary);
        }
        else
        {
            cout << "Attack impossible" << endl;
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
    
}

