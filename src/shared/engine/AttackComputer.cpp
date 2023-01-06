#include "AttackComputer.h"

#include <vector>
#include <map>
#include <functional>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace state;

namespace engine{

    void printVec(vector<int> dices){
        for(auto d : dices){
            cout<< d << "," ;
        }
        cout<<endl;
    }
    Dice dice(1,6);

    int AttackComputer::attackSimple(int nAttacker, int nDefender) {

        if (nAttacker > 3 || nDefender > 2){
            cerr << __FUNCTION__ <<" n'est valide que pour nAttacker > 3 et nDefender > 2)" << endl;
            exit(1);
        }

        vector <int> attDices(nAttacker, 0);
        vector <int> defDices(nDefender, 0);
        #ifdef DEBUG
            cout << "---------------------------" << endl;
            cout << __FUNCTION__ << endl;
        #endif

        generate(attDices.begin(), attDices.end(), bind(&Dice::thrown, &dice));
        generate(defDices.begin(), defDices.end(), bind(&Dice::thrown, &dice));

        #ifdef DEBUG
            cout << "Avant tri" << endl;
            printVec(attDices);
            printVec(defDices);
        #endif

        sort(attDices.begin(), attDices.end(), greater<int>());
        sort(defDices.begin(), defDices.end(), greater<int>());

        #ifdef DEBUG
            cout << "Apres tri" << endl;
            printVec(attDices);
            printVec(defDices);
        #endif

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
    map<string,int> AttackComputer::attackNvM(int nAttacker, int nDefender)
    {
        std::cout << "In attackNvM" << "\n";
        #ifdef DEBUG
            cout << "---------------------------" << endl;
            cout << __FUNCTION__ << endl;
            cout << "Number of att : " << nAttacker << endl;
            cout << "Number of def : " << nDefender << endl;
        #endif

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


        #ifdef DEBUG
            cout << "## Summary" << endl;
            for (auto it = attackSummary.begin(); it != attackSummary.end(); it++) {
                cout << it->first << ": " << it->second << endl;
            }
        #endif

        return attackSummary;
    }

    vector<vector<double>> AttackComputer::probaTable = FileOps::csvParserD("res/proba.csv");

    // TO-DO :: Improve test less than 20 and compute localy if not 
    double AttackComputer::victoryProba (int nAttacker, int nDefender){
        if((nAttacker>0) & (nDefender > 0)){
            return probaTable[nAttacker-1][nDefender-1];
        }
        else{
            cerr << "Nombre d'attaquant ou de défenseur nul" <<endl;
            return -1;
        }
    }
}