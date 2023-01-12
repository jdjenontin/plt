#include "NormalAi.h"
#include <iostream>
#include <chrono>
#include <engine.h>
#include <vector>
#include <thread>
#include <algorithm>
#include <list>
#include <iterator>

using namespace engine;
using namespace state;
using namespace std;

using namespace std;
using namespace state;

extern vector<shared_ptr<state::Country>> v_listcountry; // TO-DO Delete 

namespace ai{


    /*void NormalAi::place(){
        std::vector<int> nbOfCountryC = {9,4,6,7,12,4};
        std::vector<int> ai_presence =  this->presenceOnContinents();

        std::vector<int> unOwnedCountries(6,0);

        std::transform(nbOfCountryC.begin(), nbOfCountryC.end(), ai_presence.begin(), 
                        unOwnedCountries.begin(), [](int a, int b) { return a - b; });

        return;
    
    }*/

NormalAi::NormalAi () {
}

NormalAi::NormalAi(shared_ptr<State> a_state) : Ai(a_state){
    
}

NormalAi::~NormalAi() {
    
}

//La stratégie du bot est de conquérir un maximux de pays sur un même continent puis une fois cela fait il attack un autre continent
void NormalAi::execute (){
    std::cout << "Execute du bot Normal " << std::endl;

    std::sort(countriesList.begin(), countriesList.end(), state::Country::idComparaison);
    std::vector<int> continentsPresence(player->presenceOnContinents());
    std::vector<int> newContinentsPresence = continentsPresence;
    int nbUnequal = 0;
    std::vector<int> totalNbOfCountries = {9,4,6,7,12,4};
    int testContinentsPresence = 0;

    for(int i = 0; i<continentsPresence.size(); i++){
        if (continentsPresence.at(i) != totalNbOfCountries.at(i)){
            nbUnequal++;
        }
    }

    if (nbUnequal == 0) {
        cout << "Heuristic Ai won" << endl;
        cout <<"NbCOuntries in Oceania:" << continentsPresence.at(5);
    }

    else if (nbUnequal == totalNbOfCountries.size()) {
        int idContinentToAttack = (distance(continentsPresence.begin(), max_element(continentsPresence.begin(), continentsPresence.end())));
        continentToAttack = (state::Continent) idContinentToAttack;
        cout <<"Continent a attacker: " << continentToAttack << endl;
        cout <<"NbCOuntries in Oceania:" << continentsPresence.at(5);
    }
    
    else{

        int index = 0;
        for (index; index<continentsPresence.size(); index++){
            if(continentsPresence.at(index) == totalNbOfCountries.at(index)) break;
        }

        switch(index) {
            case 0:
                if(continentsPresence.at(1) != totalNbOfCountries.at(1)) continentToAttack = AMERIQUE_SUD;
                else if(continentsPresence.at(3) != totalNbOfCountries.at(3)) continentToAttack = EUROPE;
                else if(continentsPresence.at(4) != totalNbOfCountries.at(4)) continentToAttack = ASIE;
                
                break;

            case 1:
                if(continentsPresence.at(2) != totalNbOfCountries.at(2)) continentToAttack = AFRIQUE;
                else if(continentsPresence.at(0) != totalNbOfCountries.at(0)) continentToAttack = AMERIQUE_NORD;

                break;

            case 2:
                if(continentsPresence.at(1) != totalNbOfCountries.at(1)) continentToAttack = AMERIQUE_SUD;
                else if(continentsPresence.at(3) != totalNbOfCountries.at(3)) continentToAttack = EUROPE;
                else if(continentsPresence.at(4) != totalNbOfCountries.at(4)) continentToAttack = ASIE;
                break;

            case 3:
                if(continentsPresence.at(2) != totalNbOfCountries.at(2)) continentToAttack = AFRIQUE;
                else if(continentsPresence.at(0) != totalNbOfCountries.at(0)) continentToAttack = AMERIQUE_NORD;
                else if(continentsPresence.at(4) != totalNbOfCountries.at(4)) continentToAttack = ASIE;
                break;

            case 4:
                if(continentsPresence.at(5) != totalNbOfCountries.at(5)) continentToAttack = OCEANIE;
                else if(continentsPresence.at(2) != totalNbOfCountries.at(2)) continentToAttack = AFRIQUE;
                else if(continentsPresence.at(3) != totalNbOfCountries.at(3)) continentToAttack = EUROPE;
                else if(continentsPresence.at(0) != totalNbOfCountries.at(0)) continentToAttack = AMERIQUE_NORD;
                
                break;

            case 5:
                if(continentsPresence.at(4) != totalNbOfCountries.at(4)) continentToAttack = ASIE;
                break;
        }

        cout <<"Continent a attacker: " << continentToAttack << endl;
        cout <<"index:" << index << endl;
        cout <<"NbCOuntries in Oceania:" << continentsPresence.at(5) << endl;
    }

    place();
    attack();
    //reinforce();
}

void NormalAi::place (){
    std::cout << "Place du bot Heuristic" << std::endl;
    int minNbTroops = 7;
    int countriesWithMaxNbTroops = 0;
    int bonus_troop = player->continentBonusTroop();

    for(int i = 0; i < bonus_troop; i++){
        for (auto country : countriesList){
            if ((country->getContinent() == continentToAttack) & (country->getNumberOfTroop()) < minNbTroops){
                std::cout << "Placing troop in " << country->getName() << std::endl;
                country->addTroop(1);
                break;
            }

        }

        bonus_troop--;
        std::cout << "Heuristic Ai place troops" << std::endl;
    }  
}

void NormalAi::execute(std::shared_ptr<state::Player> a_player)
{
    player = a_player;
    this->execute();
}

void NormalAi::attack (){

    std::cout << "Attack du bot Normal " << std::endl;
    bool canAttack = true;
    std::vector<int> count;
    std::vector<std::shared_ptr<Country>> aiAttackCountries;
    std::vector<int> troopsAttackCountries;
    std::vector<int> troopsDefCountries;
    std::vector<std::shared_ptr<Country>> aiAttackableCountries; // We create a list with all the countries the Ai can attack with its attack Country
    std::vector<Country> weakestCountry;
    int maxContinentId = 0;
    bool conqueredMaxCont = false;

    while(canAttack){

        //Si l'ia possède tous les pays d'un continent elle attaque le continent voisin sinon elle attaque dans ce continent
        /*switch (maxContinentId) {
            case 0:
                if(maxContinentId == 9) conqueredMaxCont = true;
                break;

            case 1:
                if(maxContinentId == 4) conqueredMaxCont = true;
                break;

            case 2:
                if(maxContinentId == 6) conqueredMaxCont = true;
                break;

            case 3:
                if(maxContinentId == 7) conqueredMaxCont = true;
                break;

            case 4:
                if(maxContinentId == 12) conqueredMaxCont = true;
                break;

            case 5:
                if(maxContinentId == 4) conqueredMaxCont = true;
                break;
        }*/
            
        for (int i=0; i<countriesList.size();i++) {
            if ((countriesList.at(i)->getNumberOfTroop() > 1) & countriesList.at(i)->getContinent() == continentToAttack) {
                aiAttackCountries.push_back(countriesList.at(i));
                troopsAttackCountries.push_back(countriesList.at(i)->getNumberOfTroop());
            }

        }
            
            //We make a list of all the countries we can attack
        for(int j=0; j<aiAttackCountries.size(); j++){
            troopsDefCountries.push_back(0);
            for(int i=0; i<42;i++) {
                if ((aiAttackCountries.at(j)->isAdjacent(i)) & (!Calculation::isCountryInList(v_listcountry.at(i), aiAttackCountries)) & (aiAttackCountries.at(j)->getNumberOfTroop()+1 > v_listcountry.at(i)->getNumberOfTroop()) & v_listcountry.at(i)->getContinent() == continentToAttack) {
                    std::cout << "The Heuristic AI can attack " << v_listcountry.at(i)->getName() << ". \n";
                    aiAttackableCountries.push_back(v_listcountry.at(i));
                    troopsDefCountries.push_back(v_listcountry.at(i)->getNumberOfTroop());
                    count.push_back(j);

                }
            }
        }

        int idStrongestCountry = distance(troopsAttackCountries.begin(), max_element(troopsAttackCountries.begin(), troopsAttackCountries.end()));
        int idWeakestCountry = distance(troopsDefCountries.begin(), min_element(troopsDefCountries.begin(), troopsDefCountries.end()));

        if (!aiAttackableCountries.empty()) {
            

            std::shared_ptr<state::Country> aiAttackCountry = aiAttackCountries.at(count.at(idWeakestCountry));
            std::shared_ptr<state::Country> aiDefCountry = aiAttackableCountries.at(idWeakestCountry); 

            std::cout << "The Heuristic AI will attack " << aiDefCountry->getName() << " with " << aiAttackCountry->getName() << "\n";
            cout << aiDefCountry->getId() << endl;

            aiAttack.setAttackCountry(aiAttackCountry);
            std::cout << "Set Attack Country" << "\n";
            aiAttack.setDefCountry(aiDefCountry);
            std::cout << "Set def country" << "\n";
            
            aiAttack.setPlayer(player);
            
            aiAttack.execute();

            std::cout << "Attacking" << std::endl;

            std::cout << "End of Attack" << endl;
        }

        std::sort(countriesList.begin(), countriesList.end(), state::Country::idComparaison);
        std::vector<int> continentsPresence(player->presenceOnContinents());
        std::vector<int> totalNbOfCountries = {9,4,6,7,12,4};
        int nbUnequal = 0;
        int testContinentsPresence = 0;

        for(int i = 0; i<continentsPresence.size(); i++){
            if (continentsPresence.at(i) != totalNbOfCountries.at(i)){
                nbUnequal++;
            }
        }

        if (nbUnequal == 0) {
            cout << "Heuristic Ai won" << endl;
        }

        else if (nbUnequal == totalNbOfCountries.size()) {
            int idContinentToAttack = (distance(continentsPresence.begin(), max_element(continentsPresence.begin(), continentsPresence.end())));
            continentToAttack = (state::Continent) idContinentToAttack;
            cout <<"Continent a attacker: " << continentToAttack << endl;
        }
        
        else{

            int index = 0;
            for (index; index<continentsPresence.size(); index++){
                if(continentsPresence.at(index) == totalNbOfCountries.at(index)) break;
            }

            switch(index) {
                case 0:
                    if(continentsPresence.at(1) != totalNbOfCountries.at(1)) continentToAttack = AMERIQUE_SUD;
                    else if(continentsPresence.at(3) != totalNbOfCountries.at(3)) continentToAttack = EUROPE;
                    else if(continentsPresence.at(4) != totalNbOfCountries.at(4)) continentToAttack = ASIE;
                    
                    break;

                case 1:
                    if(continentsPresence.at(2) != totalNbOfCountries.at(2)) continentToAttack = AFRIQUE;
                    else if(continentsPresence.at(0) != totalNbOfCountries.at(0)) continentToAttack = AMERIQUE_NORD;

                    break;

                case 2:
                    if(continentsPresence.at(1) != totalNbOfCountries.at(1)) continentToAttack = AMERIQUE_SUD;
                    else if(continentsPresence.at(3) != totalNbOfCountries.at(3)) continentToAttack = EUROPE;
                    else if(continentsPresence.at(4) != totalNbOfCountries.at(4)) continentToAttack = ASIE;
                    break;

                case 3:
                    if(continentsPresence.at(2) != totalNbOfCountries.at(2)) continentToAttack = AFRIQUE;
                    else if(continentsPresence.at(0) != totalNbOfCountries.at(0)) continentToAttack = AMERIQUE_NORD;
                    else if(continentsPresence.at(4) != totalNbOfCountries.at(4)) continentToAttack = ASIE;
                    break;

                case 4:
                    if(continentsPresence.at(5) != totalNbOfCountries.at(5)) continentToAttack = OCEANIE;
                    else if(continentsPresence.at(2) != totalNbOfCountries.at(2)) continentToAttack = AFRIQUE;
                    else if(continentsPresence.at(3) != totalNbOfCountries.at(3)) continentToAttack = EUROPE;
                    else if(continentsPresence.at(0) != totalNbOfCountries.at(0)) continentToAttack = AMERIQUE_NORD;
                    
                    break;

                case 5:
                    if(continentsPresence.at(4) != totalNbOfCountries.at(4)) continentToAttack = ASIE;
                    break;
            }
            
            cout <<"Continent a attacker: " << continentToAttack << endl;
            cout <<"index:" << index << endl;
            cout <<"NbCOuntries in Oceania:" << continentsPresence.at(5) << endl;
        }

        canAttack = false;

    }


}

void NormalAi::reinforce (){

}
    
};