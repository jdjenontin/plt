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

    std::vector<state::Continent> allContinents = {AMERIQUE_NORD, AMERIQUE_SUD, AFRIQUE, EUROPE, ASIE, OCEANIE};
    swapContinentToAttack(allContinents);
    place();
    attack();
    //reinforce();
}

void NormalAi::place (){
    std::cout << "Place du bot Heuristic" << std::endl;
    int minNbTroops = 7;

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
    countriesList = player->getCountriesList();
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

    while(canAttack){
        
        for (int i=0; i<countriesList.size();i++) {
            if ((countriesList.at(i)->getNumberOfTroop() > 1) & countriesList.at(i)->getContinent() == continentToAttack) {
                aiAttackCountries.push_back(countriesList.at(i));
                troopsAttackCountries.push_back(countriesList.at(i)->getNumberOfTroop());
            }

        }
            
        //We make a list of all the countries we can attack
        for(int j=0; j<aiAttackCountries.size(); j++){
            for(int i=0; i<42;i++) {
                if ((aiAttackCountries.at(j)->isAdjacent(i)) & (!Calculation::isCountryInList(v_listcountry.at(i), aiAttackCountries))
                     & (aiAttackCountries.at(j)->getNumberOfTroop()+1 > v_listcountry.at(i)->getNumberOfTroop()) 
                     & v_listcountry.at(i)->getContinent() == continentToAttack){

                    std::cout << "The Heuristic AI can attack " << v_listcountry.at(i)->getName() << ". \n";
                    aiAttackableCountries.push_back(v_listcountry.at(i));
                    troopsDefCountries.push_back(v_listcountry.at(i)->getNumberOfTroop());
                    count.push_back(j);
                }
            }
        }

        int idWeakestCountry = distance(troopsDefCountries.begin(), min_element(troopsDefCountries.begin(), troopsDefCountries.end()));

        if (!aiAttackableCountries.empty()) {
            

            std::shared_ptr<state::Country> aiAttackCountry = aiAttackCountries.at(count.at(idWeakestCountry));
            std::shared_ptr<state::Country> aiDefCountry = aiAttackableCountries.at(idWeakestCountry); 

            std::cout << "The Heuristic AI will attack " << aiDefCountry->getName() << " with " << aiAttackCountry->getName() << "\n";
            cout << aiDefCountry->getId() << endl;

            aiAttack.setAttackCountry(aiAttackCountry);

            aiAttack.setDefCountry(aiDefCountry);
            
            aiAttack.setPlayer(player);
            
            aiAttack.execute();

            std::cout << "End of Attack" << endl;
        }

        canAttack = false;

    }


}

void NormalAi::reinforce (){

}


void NormalAi::swapContinentToAttack(std::vector<state::Continent> continentList){
    int idContinentToAttack;
    int smallest = 100;
    int i;
    std::vector<int> totalNbOfCountries = {9,4,6,7,12,4};
    std::vector<int> continentsPresence(player->presenceOnContinents());
    std::vector<int> opponentContinentsPresence;
    std::vector<state::Continent> allContinents = {AMERIQUE_NORD, AMERIQUE_SUD, AFRIQUE, EUROPE, ASIE, OCEANIE};
    std::vector<state::Continent> continentsToTest = continentList;
    std::vector<state::Continent> listBorderContinents;

    for(i = 0; i<continentsPresence.size(); i++){
        opponentContinentsPresence.push_back(totalNbOfCountries.at(i) - continentsPresence.at(i));
    }

    if(continentsToTest.size() != 6) {
        for(int i = 0; i<continentsToTest.size(); i++) {
            Continent currentContinent = continentsToTest.at(i);
            if (opponentContinentsPresence.at((int) currentContinent) == 0){
                continentsToTest.erase(continentsToTest.begin()+i);
                allContinents.erase(allContinents.begin()+ (int) currentContinent);
            }

            else{
                continentToAttack =  currentContinent;
                return;
            }
        }

        return swapContinentToAttack(allContinents);
    }

    else {
        for (i = 0; i<opponentContinentsPresence.size(); i++) {
            if (opponentContinentsPresence.at(i) < smallest){
                if (opponentContinentsPresence.at(i) != 0){
                    smallest = opponentContinentsPresence.at(i);
                    continentToAttack = (Continent) i;
                }

                else{
                    listBorderContinents = Calculation::borderContinent((Continent) i);
                    return swapContinentToAttack(listBorderContinents);
                }
                
            }
        }
    }
}

};