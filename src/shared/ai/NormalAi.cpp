#include "NormalAi.h"
#include <iostream>
#include <chrono>
#include <engine.h>
#include <vector>
#include <thread>
#include <algorithm>
#include <list>
#include <iterator>

// #define DEBUG 1 

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
#ifdef DEBUG
    std::cout << "Normal AI " << __func__ << std::endl;
#endif
    
    std::vector<int> allContinents(6, 1);

    swapContinentToAttack(allContinents);

    place();
    attack();
    reinforce();
}

void NormalAi::place (){
    
    std::vector<int> continentsPresence(player->presenceOnContinents());
    std::vector<int> totalNbOfCountries = {9,4,6,7,12,4};


    int bonus_troop = player->continentBonusTroop();

    for(int i = 0; i < bonus_troop; i++){
        for (auto country : countriesList){
            vector<shared_ptr<Country>> countriesAdjacent = Computation::adjacentCountries(state, country);
            if (((country->getContinent() == continentToAttack) | (std::find(borderCountriesId.begin(), borderCountriesId.end(), country->getId()) != borderCountriesId.end())) 
                & ((country->getNumberOfTroop()) < minNbTroops[country->getContinent()])){
                
                for(auto adjCountry : countriesAdjacent){
                    if(!Calculation::isCountryInList(adjCountry, countriesList)){
                        country->addTroop(1);
                        break;
                    }
                }
                
            }
        }
        bonus_troop--;
    }

    for(int i = 0; i<6; i++){
        if(continentsPresence[i] == totalNbOfCountries[i]){
            minNbTroops[i]+= 5;
        }
        else{
            minNbTroops[i] = 10;
        }
    }
}

void NormalAi::execute(std::shared_ptr<state::Player> a_player)
{
    player = a_player;
    countriesList = player->getCountriesList();
    this->execute();
}

void NormalAi::attack (){

    bool canAttack = true;
    std::vector<int> count;
    std::vector<std::shared_ptr<Country>> aiAttackCountries;
    std::vector<int> troopsAttackCountries;
    std::vector<int> troopsDefCountries;

    std::vector<std::shared_ptr<Country>> aiAttackableCountries; // We create a list with all the countries the Ai can attack with its attack Country

    while(canAttack){
        
        for (unsigned int i=0; i<countriesList.size();i++) {
            if ((countriesList.at(i)->getNumberOfTroop() > 1) & 
                ((countriesList.at(i)->getContinent() == continentToAttack) | (std::find(borderCountriesId.begin(), borderCountriesId.end(), countriesList.at(i)->getId()) != borderCountriesId.end()))) {
                aiAttackCountries.push_back(countriesList.at(i));
                troopsAttackCountries.push_back(countriesList.at(i)->getNumberOfTroop());
            }

        }
        

        // TO-DO : Use Computation::adjacentCountries 
        //We make a list of all the countries we can attack
        for(unsigned int j=0; j<aiAttackCountries.size(); j++){
            for(int i=0; i<42;i++) {
                
                if ((aiAttackCountries.at(j)->isAdjacent(i)) & (!Calculation::isCountryInList(v_listcountry.at(i), countriesList))
                     & (v_listcountry.at(i)->getContinent() == continentToAttack)){
                    aiAttackableCountries.push_back(v_listcountry.at(i));
                    troopsDefCountries.push_back(v_listcountry.at(i)->getNumberOfTroop());
                    count.push_back(j);
                }
            }
        }

        int idWeakestCountry = distance(troopsDefCountries.begin(), min_element(troopsDefCountries.begin(), troopsDefCountries.end()));
            
        if (!aiAttackableCountries.empty()){
            std::shared_ptr<state::Country> aiAttackCountry = aiAttackCountries.at(count.at(idWeakestCountry));
            std::shared_ptr<state::Country> aiDefCountry = aiAttackableCountries.at(idWeakestCountry); 

            aiAttack.setAttackCountry(aiAttackCountry);
            aiAttack.setDefCountry(aiDefCountry);
            aiAttack.setPlayer(player);
            aiAttack.execute();

        }

        canAttack = false;

    }


}

void NormalAi::reinforce (){

    std::vector<std::shared_ptr<state::Country>> countriesAdjacent;
    std::shared_ptr<state::Country> testCountryOne;
    unsigned int i;

    for(i = 0; i<countriesList.size(); i++){
        testCountryOne = countriesList[i];
        if (((testCountryOne->getContinent() == continentToAttack) | (std::find(borderCountriesId.begin(), borderCountriesId.end(), testCountryOne->getId()) != borderCountriesId.end()))
            & (testCountryOne->getNumberOfTroop() < 20)){
            countriesAdjacent = Computation::adjacentCountries(state, testCountryOne);
            break;
        }
    }

    for(auto testCountryTwo: countriesAdjacent){
        int numTroopsCountry  = testCountryTwo->getNumberOfTroop();
        int troopsToAdd = (int) (numTroopsCountry/2);
        if((Calculation::isCountryInList(testCountryTwo, countriesList)) & (numTroopsCountry > 1)){
            testCountryOne->addTroop(troopsToAdd);
            testCountryTwo->reduceTroop(troopsToAdd);
        }
    }
}


void NormalAi::swapContinentToAttack(std::vector<int> continentList){
    int smallest = 100;
    unsigned int i;
    std::vector<int> totalNbOfCountries = {9,4,6,7,12,4};
    std::vector<int> continentsPresence(player->presenceOnContinents());
    std::vector<int> opponentContinentsPresence;
    std::vector<int> allContinents(6,1);
    std::vector<int> continentsToTest = continentList;
    std::vector<int> listBorderContinents;
    std::vector<int> newContinentsToTest;
    unsigned int counter = 0;

    for(i = 0; i<continentsPresence.size(); i++){
        opponentContinentsPresence.push_back(totalNbOfCountries.at(i) - continentsPresence.at(i));
    }

    if(continentsToTest.size() != 6) {
        for(int i = 0; i<(int)allContinents.size(); i++) {
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