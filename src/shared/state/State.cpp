#include "State.h"
#include <iostream>
#include <map>

#include <random>

#include "Calculation.h"


using namespace std;

namespace state
{
    
State::State(){
    
}

State::~State(){
    
}

State::State(int n_player){
    numberPlayer = n_player;

    for(int i = 0; i < n_player; i++){
        playersList.push_back(Player());
    }
}

void State::init()
{
    //Création de la liste de tous les pays
    std::vector<std::string> countriesNames = {"Alaska", "Territoire du Nord-Ouest", "Alberta", "Ontario", "Groenland", "Quebec", "Ouest des Etat-Unis", "Est des Etats-Unis", 
                        "Amerique Centrale", "Venezuela", "Perou", "Bresil", "Argentine", "Afrique du Nord", "Egypte", "Afrique de l'Est",
                         "Congo", "Afrique du Sud", "Madagascar", "Islande", "Grande-Bretagne", "Scandinavie", "Europe du Nord",
                          "Ukraine", "Europe de l'Ouest", "Europe du Sud", "Moyen-Orient", "Afghanistan", "Ural", "Siberie", "Yakutsk",
                           "Irkoutsk", "Mongolie", "Kamchatka", "Japon", "Chine", "Inde", "Siam", "Indonesie", "Nouvelle-Guinee", "Australie Orientale",
                            "Australie Occidentale"};

    std::map <int, string> listcountry;

    for(int i = 0; i < (int)countriesNames.size(); i++) {
        listcountry[i] = countriesNames[i];
    }

    for (map<int,string>::iterator it=listcountry.begin(); it!=listcountry.end(); ++it) {
        Country country(it->second, it->first);
        countriesList.push_back(country);
    }

    //Affectation des pays et troupes aux joueurs
    vector<int> affectation_order;
    Calculation calc;
    affectation_order = calc.shuffledTab(42);

    // Attribution des pays : Dans certains cas les premiers ont plus de pays que les derniers
    int j = 0;
    for(int i = 0; i != 42; i++){
        countriesList[i].addNumberTroop(2);
        playersList[j].addCountry(countriesList[i]);
        j++;
        j %= numberPlayer;
    }
    
    // Attribution des soldats :

    map<int, int> initialTroopMap {{2,45}, {3,35}, {4,30}, {5,25}};

    int initialTroop = initialTroopMap[numberPlayer];

    int minTroopPerTeritory = (int) initialTroop/numberPlayer;

    for (int i = 0; i != numberPlayer; i++){
        vector<Country> playerCountries = playersList[i].getListCountry();
        int minTroopPerTeritory = (int) initialTroop/playerCountries.size();

        for(auto country : playerCountries){
            country.addNumberTroop(minTroopPerTeritory);
        }

        int remaningTroop = initialTroop%playerCountries.size();
    }


}


} // namespace state
