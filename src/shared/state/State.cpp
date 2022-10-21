#include "State.h"
#include <iostream>
#include <map>
#include <iterator>

using namespace std;

namespace state
{
    
State::State(){
    
}

State::~State(){

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
}

std::vector<Country> State::getListCountry() {
    return countriesList;
}

std::vector<Card> State::getListCard() {
    return cardList;
}


} // namespace state
