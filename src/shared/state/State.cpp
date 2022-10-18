#include "State.h"
#include <iostream>
#include <map>

#include <random>

#include "Dice.h"
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

    //Creation de la liste de toutes les cartes 
    for(int i = 0; i < 42; i+=3){
        Card card1(countriesNames[i], Infantry);
        cardList.push_back(card1);

        Card card2(countriesNames[i+1], Cavalry);
        cardList.push_back(card2);

        Card card3(countriesNames[i+2], Artillery);
        cardList.push_back(card3);
    }
    //Affectation des pays et troupes aux joueurs
    vector<int> affectation_order;
    Calculation calc;
    affectation_order = calc.shuffledTab(42);

    // Attribution des pays : Dans certains cas les premiers ont plus de pays que les derniers
    int j = 0;
    for(auto i : affectation_order){
        countriesList[i].addNumberTroop(2);
        playersList[j].addCountry(countriesList[i]);
        j++;
        j %= numberPlayer;
    }
    
    // Attribution des soldats :
    
    map<int, int> initialTroopMap {{2,45}, {3,35}, {4,30}, {5,25}};

    
    cout << initialTroopMap[numberPlayer] << endl;
    int initialTroop = initialTroopMap[numberPlayer];

    for (int i = 0; i != numberPlayer; i++){
        vector<Country> playerCountries = playersList[i].getListCountry();
        int minTroopPerTeritory = (int) initialTroop/playerCountries.size();
        
        // Ajout d'un nombre min de troupe à tous less territoire
        for(auto country : playerCountries){
            country.addNumberTroop(minTroopPerTeritory);
        }
        
        // Ajoout du nombre de troupe restant de façon aléatoire sur le reste des territoires 
        int remaningTroop = initialTroop%playerCountries.size();

        cout << "Remaining ::" << remaningTroop << endl;

        Dice dice(0, playerCountries.size() - 1);

        for(int k = 0; k != remaningTroop; k++)
        {
            int test = dice.thrown();
            cout << "Throw " << test << endl;
            cout << playerCountries[test].getNumberTroop() << endl;
            playerCountries[test].addNumberTroop(1);
            cout << "GDehrtdre" <<playerCountries[test].getNumberTroop() << endl;
        }
        

    }


}

std::vector<Country> State::getListCountry() {
    return countriesList;
}

std::vector<Card> State::getListCard() {
    return cardList;
}

const std::vector<Player>& State::getPlayersList() const{
    return playersList;
}

} // namespace state
