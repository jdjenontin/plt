#include <iostream>
#include <random>
#include <chrono>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}

// Fin test SFML

#include <state.h>

using namespace std;
using namespace state;

vector<Country> v_listcountry;
//la liste est definitive, ne touche jamais.

void init_player(Player player1, Player player2, Player player3){
    Dice dice(3,5);

    for(int i = 0; i < 14; i+=3){
        player1.addCountry(v_listcountry[i]);
        v_listcountry[i].addNumberTroop(dice.thrown());
        player2.addCountry(v_listcountry[i+1]);
        v_listcountry[i+1].addNumberTroop(dice.thrown());
        player3.addCountry(v_listcountry[i+2]);
        v_listcountry[i+2].addNumberTroop(dice.thrown());
    }
}

void testgame(){
    State state;

    int num_player;

    cout << "choose the number of player :(you need choose 3 for now)";
    cin >> num_player;

    if(num_player != 3) return;

    Player player1;
    Player player2;
    Player player3;

    state.init();

//initialiser la liste
    v_listcountry = state.getListCountry();
    
//ajouter des pays au joueur1
//**************************************//
    init_player(player1, player2, player3);
//**************************************//

//jouer
    while(state.playing){
        
    }


//choisis les pays attaquant et defensifs
    int c_attack, c_defender;

    cout << "choose the attack country's number :";
    cin >>  c_attack;

    cout << "choose the defend country's number :";
    cin >> c_defender;

//detecter les pays adjacents
//**************************************//
    if(v_listcountry[c_attack].isAdjacent(c_defender))
        cout << "isadjacent" << endl;
    else 
        cout << "notadjacent" << endl;

//**************************************//
    int n_attacker, n_defender;

    cout << "Please set the forces of the attacker :";
    cin >> n_attacker;
    v_listcountry[c_attack].addNumberTroop(n_attacker);

    cout << "Please set the forces of the defender :";
    cin >> n_defender;
    v_listcountry[c_defender].addNumberTroop(n_defender);
//donner les troups aux deux pays 

    cout << "attacker's forces :"<< v_listcountry[c_attack].getNumberTroop() << endl;
    cout << "defender's forces :"<< v_listcountry[c_defender].getNumberTroop() << endl;

    int attack = 1;

    while(attack){
        attack = player1.attack(v_listcountry[c_attack], v_listcountry[c_defender]);
    }

    cout << v_listcountry[c_attack].getNameCountry() << " have " << v_listcountry[c_attack].getNumberTroop() << " troops" << endl; 
    cout << v_listcountry[c_defender].getNameCountry() << " have " << v_listcountry[c_defender].getNumberTroop() << " troops" << endl;

//*************************************//
//test pour calculer la probabilte de bataille 

/*  cout << exemple.getX() << endl;
    cout << player1.getownTroop() << endl;
    cout << v_listcountry[4].getNameCountry() << v_listcountry[4].getNumberCountry() << endl;
    cout << player1.getListCountry()[0].getNameCountry() << " " << player1.getListCountry()[0].getNumberCountry() << endl;
*/

}

int main(int argc,char* argv[])
{
    //testSFML();
    testgame();

    return 0;
}
