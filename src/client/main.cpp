#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include <sstream>
#include <state.h>

using namespace std;
using namespace state;
using namespace sf;

void testSFML() {
    // create the window
    RenderWindow window(sf::VideoMode(1280, 886), "My window");

    Texture t;

    t.loadFromFile("res/carte.png");

    Sprite background(t);
    
    Color color;

    CircleShape cir(25);

    cir.setFillColor(color.Black);

    Font font;
    if (!font.loadFromFile("res/arial/arial.ttf"))
        return;
    Text text1("1", font, 30);

    Text text2("X : 0", font, 20);
    text2.setFillColor(color.Black);
    Text text3("Y : 0", font, 20);
    text3.setFillColor(color.Black);

    text2.setPosition(1150,25);
    text3.setPosition(1150,50);

    text1.setFillColor(color.Blue);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        ostringstream flux1, flux2;

        Vector2i pos = Mouse::getPosition(window);

        Event mouse;
        while (window.pollEvent(mouse))
        {
            if (mouse.type == Event::Closed)
                window.close();
            if (mouse.type == Event::MouseButtonPressed)
                if (mouse.key.code == Mouse::Left) 
                {
                    text1.setPosition(pos.x, pos.y);
                }
                else if (mouse.key.code == Mouse::Right) 
                {
                    cir.setPosition(pos.x, pos.y);
                }
        }

        flux1 << "X : ";
        flux1 << pos.x;

        String const str1 = flux1.str();

        flux2 << "Y : ";
        flux2 << pos.y;

        String const str2 = flux2.str();
        
        text2.setString(str1);
        text3.setString(str2);

        window.clear(Color::White);	
        window.draw(background);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.draw(cir);

        window.display();
    }
}

// Fin test SFML

vector<Country> v_listcountry;
//la liste est definitive, ne touche jamais.

void listCountries(Player player){
    cout << "listCountires" << endl;
    vector<Country> listcountry = player.getListCountry();

    for(unsigned i = 0; i < listcountry.size(); i++){
        cout << listcountry[i].getNumberCountry();
        cout << ' ' << listcountry[i].getNumberTroop() << endl;
    }
}

void jouer(Player player){
    //choisir les pays attaquant et defensifs
    int c_attack, c_defender;

    listCountries(player);

    cout << "choose the attack country's number :";
    cin >>  c_attack;

    cout << "choose the defend country's number :";
    cin >> c_defender;

//detecter les pays adjacents
//**************************************//
/*    if(v_listcountry[c_attack].isAdjacent(c_defender))
        cout << "isadjacent" << endl;
    else 
        cout << "notadjacent" << endl;
*/
//**************************************//
/*    int n_attacker, n_defender;

    cout << "Please set the forces of the attacker :";
    cin >> n_attacker;
    v_listcountry[c_attack].addNumberTroop(n_attacker);

    cout << "Please set the forces of the defender :";
    cin >> n_defender;
    v_listcountry[c_defender].addNumberTroop(n_defender); */
//donner les troups aux deux pays 

/*    cout << "attacker's forces :"<< v_listcountry[c_attack].getNumberTroop() << endl;
    cout << "defender's forces :"<< v_listcountry[c_defender].getNumberTroop() << endl;

    int attack = 1;

    while(attack){
        attack = player.attack(v_listcountry[c_attack], v_listcountry[c_defender]);
    }

    cout << v_listcountry[c_attack].getNameCountry() << " have " << v_listcountry[c_attack].getNumberTroop() << " troops" << endl; 
    cout << v_listcountry[c_defender].getNameCountry() << " have " << v_listcountry[c_defender].getNumberTroop() << " troops" << endl; */
//*************************************//
//test pour calculer la probabilte de bataille 

/*  cout << exemple.getX() << endl;
    cout << player1.getownTroop() << endl;
    cout << v_listcountry[4].getNameCountry() << v_listcountry[4].getNumberCountry() << endl;
    cout << player1.getListCountry()[0].getNameCountry() << " " << player1.getListCountry()[0].getNumberCountry() << endl;
*/
}

/*void init_player(Player &player1, Player &player2, Player &player3){
    Dice dice(3,5);

    for(int i = 0; i < 42; i+=3){
        player1.addCountry(v_listcountry[i]);
        v_listcountry[i].addNumberTroop(dice.thrown());
        player2.addCountry(v_listcountry[i+1]);
        v_listcountry[i+1].addNumberTroop(dice.thrown());
        player3.addCountry(v_listcountry[i+2]);
        v_listcountry[i+2].addNumberTroop(dice.thrown());
    }
}
*/

void testgame(){
    int num_player;

    cout << "choose the number of player :(you need choose 3 for now) ";
    cin >> num_player;

    State state(num_player);

    Player player1;
    Player player2;
    Player player3;

    state.init();

//initialiser la liste
    v_listcountry = state.getListCountry();
    
//ajouter des pays au joueur1
//**************************************//
    //init_player(player1, player2, player3);
    vector<Player> pList = state.getPlayersList();
    
    for(auto player : pList){
        cout << "Number of country : " << player.getListCountry().size() << endl;  
        }
//**************************************//

//jouer
    while(1){
        cout << "s" << endl;
        for(vector<Player>::iterator it = pList.begin(); it != pList.end(); ++it){
            jouer(*it);
        }
    }

}

int main(int argc,char* argv[])
{
    testSFML();
    //testgame();

    return 0;
}
