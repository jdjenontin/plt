#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>

using namespace std;
using namespace state;

vector<string> vec= {"france", "germany", "england", "chine", "poland"};

vector<Country> v_listcountry;
//la liste est definitive, ne touche jamais.

void buildCountry (int number, string name) {
    Country country(name, number);
    v_listcountry.push_back(country);
}

int main(int argc,char* argv[])
{
    Exemple exemple;
    exemple.setX(53);

    Player player1;
    Player player2;
    Player player3;

    map <int,string> listcountry;

    for(int i = 0; i < (int)vec.size(); i++) {
        listcountry[i] = vec[i];
    }

    for (map<int,string>::iterator it=listcountry.begin(); it!=listcountry.end(); ++it) {
        buildCountry(it->first, it->second);
    }

  //  player1.attack(v_listcountry[])

  //  if(player1.winAttack)
    player1.addCountry(v_listcountry[4]);
    player1.addCountry(v_listcountry[3]);
    player1.addCountry(v_listcountry[2]);
    player1.addCountry(v_listcountry[1]);

    cout << "It works !" << endl;
    cout << exemple.getX() << endl;
    cout << player1.getownTroop() << endl;
    cout << v_listcountry[4].getNameCountry() << v_listcountry[4].getNumberCountry() << endl;
    cout << player1.getListCountry()[0].getNameCountry() << " " << player1.getListCountry()[0].getNumberCountry() << endl;

    return 0;
}
