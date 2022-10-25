#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>
#include <sstream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include <sstream>
#include <state.h>

using namespace std;
using namespace state;
using namespace sf;

vector<vector<int>> PosCountries = {{100,140},{210,135},{204,208},{290,220},{446,90},{367,227},
                                    {208,302},{298,327},{225,416},{310,480},{327,593},{400,567},
                                    {341,685},{602,525},{695,489},{752,587},{689,637},{704,748},
                                    {815,750},{550,180},{530,274},{648,160},{638,286},{750,249},
                                    {563,361},{664,362},{784,453},{863,323},{877,203},{940,149},
                                    {1033,115},{1021,224},{1035,301},{1130,122},{1171,267},{1000,372},
                                    {931,466},{1028,476},{1060,608},{1166,593},{1202,711},{1106,739},
};

Font font;

vector<Country> v_listcountry;

Color blue(0, 0, 255, 200);
Color red(255, 0, 0, 200);
Color green(0, 255, 0, 200);

vector<Color> colors = {blue, red, green};


void affiche_message(RenderWindow &window, Vector2i pos){
    ostringstream flux;
    Color color;
    int numCountry;

    Text text("default", font, 25);

    for(unsigned i = 0; i < PosCountries.size(); i++){
        if((abs(pos.x - PosCountries[i][0]) < 30 ) && (abs(pos.y - PosCountries[i][1]) < 30 ))
            numCountry = i;
    }

    flux << "you choose the country ";
    flux << v_listcountry[numCountry].getNameCountry();
    flux << "\n";
    flux << "number of country is ";
    flux << numCountry;

    text.setString(flux.str());
    text.setPosition(50, 900);
    text.setFillColor(color.Black);
    window.draw(text);
    
}

void init_button(RenderWindow &window, vector<Player> &pList, Texture circle){
    Color color;

    for(unsigned j = 0; j < pList.size(); j++){
        for(unsigned i = 0; i < pList[j].getListCountry().size(); i++){
            CircleShape c(25);
            vector<Country*> cList= pList[j].getListCountry();

            int num = cList[i]->getNumberCountry();
            c.setTexture(&circle); // texture is a sf::Texture
            c.setTextureRect(IntRect(2, 2, 21, 20));
            c.setPosition(PosCountries[num][0] - 20, 
                            PosCountries[num][1] - 20);
            c.setFillColor(colors[j]);
            window.draw(c);

            Text text("1", font, 25);

            text.setString(to_string(cList[i]->getNumberTroop()));
            text.setFillColor(color.Black);
            text.setPosition(PosCountries[num][0] - 5, PosCountries[num][1] - 11);
            text.Bold;
            window.draw(text); 
        }
    }

}

void testSFML(vector<Player> &pList) {
    // create the window
    RenderWindow window(sf::VideoMode(1280, 986), "My window", Style::Titlebar);

    Texture t, circle;

    t.loadFromFile("res/carte.png");
    circle.loadFromFile("res/button.png");
    circle.setSmooth(true);

    Sprite background(t);
    
    Color color;

    CircleShape cir(25);

    cir.setTexture(&circle); // texture is a sf::Texture
    cir.setTextureRect(IntRect(2, 2, 21, 20));

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



                    // a faire 
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

        init_button(window, pList, circle);
        affiche_message(window, pos);

        window.display();
    }
}

// Fin test SFML
//la liste est definitive, ne touche jamais.

void jouer(Player player){
    //choisir les pays attaquant et defensifs
    int c_attack, c_defender;

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

    state.init();

//initialiser la liste
    v_listcountry = state.getListCountry();
    
//ajouter des pays au joueur1
//**************************************//
    //init_player(player1, player2, player3);
    vector<Player> pList = state.getPlayersList();
    
    // for(auto player : pList){
    //     cout << "Number of country : " << player.getListCountry().size() << endl;  
    //     }
    
    testSFML(pList);
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
    testgame();
    //testgame();

    return 0;
}
