#include "NormalAi.h"
#include <iostream>
#include <chrono>
#include <engine.h>
#include <vector>
#include <thread>
#include <algorithm>
#include <list>
#include <iterator>


using namespace std;
using namespace state;

extern vector<shared_ptr<state::Country>> v_listcountry; // TO-DO Delete 

namespace ai{


NormalAi::NormalAi () {
}

NormalAi::NormalAi(shared_ptr<State> a_state) : Ai(a_state){
    
}

NormalAi::~NormalAi() {
    
}

//La stratégie du bot est de conquérir un maximux de pays sur un même continent puis une fois cela fait il attack un autre continent
void NormalAi::execute (){
    
    std::vector<int> totalNbOfCountries = {9,4,6,7,12,4};
    std::vector<int> continentsPresence(player->presenceOnContinents());
    std::vector<int> opponentContinentsPresence;
    std::vector<int> allContinents(6, 1);

    cout << "Execute IA Heu" << endl;

    swapContinentToAttack(allContinents);
    int minimumPresence = 100;

    int i;

    for(i = 0; i<continentsPresence.size(); i++){
        opponentContinentsPresence.push_back(totalNbOfCountries.at(i) - continentsPresence.at(i));

        if ((opponentContinentsPresence.at(i) < minimumPresence) & (opponentContinentsPresence.at(i) != 0)){
            minimumPresence = opponentContinentsPresence.at(i);
            continentToReinforce = (Continent) i;
        }
    }

    cout << "Continent a renforcer: " << continentToReinforce << endl; 
    cout << "Continent a attacker: " << continentToAttack << endl; 

    place();
    attack();
    reinforce();
}

void NormalAi::place (){
    //std::cout << "Place du bot Heuristic" << std::endl;
    int minNbTroops = 10;

    int bonus_troop = player->continentBonusTroop();

    for(int i = 0; i < bonus_troop; i++){
        for (auto country : countriesList){
            if ((country->getContinent() == continentToAttack) & (country->getNumberOfTroop()) < minNbTroops){
                //std::cout << "Placing troop in " << country->getName() << std::endl;
                country->addTroop(1);
                break;
            }

        }

        bonus_troop--;
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
    std::vector<int> borderCountriesId({v_listcountry.at(0)->getId(), v_listcountry.at(4)->getId(), v_listcountry.at(8)->getId(), v_listcountry.at(9)->getId(),
                                                            v_listcountry.at(11)->getId(), v_listcountry.at(13)->getId(), v_listcountry.at(14)->getId(), v_listcountry.at(15)->getId(),
                                                            v_listcountry.at(19)->getId(), v_listcountry.at(23)->getId(), v_listcountry.at(24)->getId(), v_listcountry.at(25)->getId(),
                                                            v_listcountry.at(26)->getId(), v_listcountry.at(27)->getId(), v_listcountry.at(28)->getId(), v_listcountry.at(33)->getId(),
                                                            v_listcountry.at(37)->getId(), v_listcountry.at(38)->getId()});

    std::vector<std::shared_ptr<Country>> aiAttackableCountries; // We create a list with all the countries the Ai can attack with its attack Country

    while(canAttack){
        
        for (int i=0; i<countriesList.size();i++) {
            if ((countriesList.at(i)->getNumberOfTroop() > 1) & 
                ((countriesList.at(i)->getContinent() == continentToAttack) | std::find(borderCountriesId.begin(), borderCountriesId.end(), countriesList.at(i)->getId()) != borderCountriesId.end())) {
                aiAttackCountries.push_back(countriesList.at(i));
                troopsAttackCountries.push_back(countriesList.at(i)->getNumberOfTroop());
            }

        }
        
        
        cout << "aiAttackCountries: " << aiAttackCountries.size() << endl;
        //We make a list of all the countries we can attack
        for(int j=0; j<aiAttackCountries.size(); j++){
            for(int i=0; i<42;i++) {
                
                if ((aiAttackCountries.at(j)->isAdjacent(i)) & (!Calculation::isCountryInList(v_listcountry.at(i), countriesList))
                     & (v_listcountry.at(i)->getContinent() == continentToAttack)){
                    cout << "Country: " << v_listcountry.at(i)->getName() << "\t Continent: " << v_listcountry.at(i)->getContinent() << endl;
                    aiAttackableCountries.push_back(v_listcountry.at(i));
                    troopsDefCountries.push_back(v_listcountry.at(i)->getNumberOfTroop());
                    count.push_back(j);
                }
            }
        }

        cout << "aiAttackCountries: " << aiAttackCountries.size() << endl;
        cout << "aiAttackableCountries: " << aiAttackableCountries.size() << endl;

        /*for (int i=0; i<aiAttackCountries.size(); i++){
            cout << "Pays " << i << ": " << aiAttackCountries.at(i)->getName() << endl;
        }*/

        cout << "Liste de tous les pays: " << v_listcountry.size() << endl;

        int idWeakestCountry = distance(troopsDefCountries.begin(), min_element(troopsDefCountries.begin(), troopsDefCountries.end()));

            
        if (!aiAttackableCountries.empty()){
            std::shared_ptr<state::Country> aiAttackCountry = aiAttackCountries.at(count.at(idWeakestCountry));
            std::shared_ptr<state::Country> aiDefCountry = aiAttackableCountries.at(idWeakestCountry); 

            std::cout << "The Heuristic AI will attack " << aiDefCountry->getName() << " with " << aiAttackCountry->getName() << "\n";
            //cout << aiDefCountry->getId() << endl;

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


void NormalAi::swapContinentToAttack(std::vector<int> continentList){
    cout << "Swap Continent IA Heu" << endl;
    int idContinentToAttack;
    int smallest = 100;
    int i;
    std::vector<int> totalNbOfCountries = {9,4,6,7,12,4};
    std::vector<int> continentsPresence(player->presenceOnContinents());
    std::vector<int> opponentContinentsPresence;
    std::vector<int> allContinents(6,1);
    std::vector<int> continentsToTest = continentList;
    std::vector<int> listBorderContinents;
    std::vector<int> newContinentsToTest;
    int counter = 0;

    for(i = 0; i<continentsPresence.size(); i++){
        opponentContinentsPresence.push_back(totalNbOfCountries.at(i) - continentsPresence.at(i));
    }

    if(continentsToTest.size() != 6) {
        for(int i = 0; i<allContinents.size(); i++) {
            for (auto testContinent : continentsToTest){
                
                if ((testContinent == i) & (opponentContinentsPresence[testContinent] == 0)){
                    allContinents[testContinent] = 1;
                }

                else if((testContinent == i) & (opponentContinentsPresence[testContinent] > 0)){
                    continentToAttack =  (Continent) testContinent;
                    return;
                }

                else{
                    counter++;
                }
                
            }

            if (counter == continentsToTest.size()){
                newContinentsToTest.push_back(i);
            }
            counter = 0;
        }

        return swapContinentToAttack(newContinentsToTest);
    }

    else {
        for (i = 0; i<opponentContinentsPresence.size(); i++) {
            if (opponentContinentsPresence[i] < smallest){
                if (opponentContinentsPresence.at(i) != 0){
                    smallest = opponentContinentsPresence[i];
                    continentToAttack = (Continent) i;
                    allContinents[i] = 0;
                }

                else{
                    listBorderContinents = Calculation::borderContinent((Continent) i);
                    allContinents[i] = 1;
                    return swapContinentToAttack(listBorderContinents);
                }
                
            }
        }
    }
}

};