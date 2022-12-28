// #include <iostream>
// #include <algorithm>

// #include "HardAi.h"

// #define DEBUG 1;

// using namespace std;
// using namespace state;

// namespace ai{

// vector<state::Country*> playerlistcountries;

// vector<int> ameriqueN(9, 0), ameriqueS(4, 0), afrique(6, 0), europe(7, 0), asie(12, 0), ocenanie(4, 0);

// vector<int> p1, p2;

// int bonus;

// HardAi::HardAi(){

// }

// HardAi::~HardAi(){

// }

// void HardAi::place(){
    
    
// #ifdef DEBUG
//     cout << "------------------------------------------" << endl;
// #endif
// }

// void HardAi::attack(){

// }

// void HardAi::reinforce(){

// }

// void HardAi::usecard(){

// }

// void HardAi::execute() {
//     listCountries = state->getCountriesList();
//     playerlistcountries = player->getListCountry();
//     bonus = player->continentBonusTroop();

//     //initialiser la liste
//     for(int i = 0; i < listCountries.size(); i++){
//         if(i < 9) ameriqueN.push_back(listCountries[i]->getNumberOfTroop());
//         else if(i < 13) ameriqueS.push_back(listCountries[i]->getNumberOfTroop());
//         else if(i < 19) afrique.push_back(listCountries[i]->getNumberOfTroop());
//         else if(i < 26) europe.push_back(listCountries[i]->getNumberOfTroop());
//         else if(i < 38) asie.push_back(listCountries[i]->getNumberOfTroop());
//         else ocenanie.push_back(listCountries[i]->getNumberOfTroop());
//     }

//     for(int i = 0; i < playerlistcountries.size(); i++){
//         int num = playerlistcountries[i]->getNumberCountry();
//         if(num < 9) ameriqueN[num]+=100;
//         else if(num < 13)   ameriqueS[num-9]+=100;
//         else if(num < 19)   afrique[num-13]+=100;
//         else if(num < 26)   europe[num-19]+=100;
//         else if(num < 38)   asie[num-26]+=100;
//         else    ocenanie[num-38]+=100;
//     }

//     //place
//     place();

//     //attack
//     attack();

//     //reinforce
//     reinforce();

//     //usecard
//     usecard();

// }

// }