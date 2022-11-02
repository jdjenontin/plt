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
#include <render.h>

using namespace std;
using namespace state;
using namespace sf;
using namespace render;

vector<vector<int>> PosCountries = {{100,140},{210,135},{204,208},{290,220},{446,90},{367,227},
                                    {208,302},{298,327},{225,416},{310,480},{327,593},{400,567},
                                    {341,685},{602,525},{695,489},{752,587},{689,637},{704,748},
                                    {815,750},{550,180},{530,274},{648,160},{638,286},{750,249},
                                    {563,361},{664,362},{784,453},{863,323},{877,203},{940,149},
                                    {1033,115},{1021,224},{1035,301},{1130,122},{1171,267},{1000,372},
                                    {931,466},{1028,476},{1060,608},{1166,593},{1202,711},{1106,739},
};

Font font;

vector<Country*> v_listcountry;

void init_text(Text &text, int x, int y, Color color){
    text.setPosition(x, y);
    text.setFillColor(color);
}

void display(RenderWindow &window, vector<Player*> &pList, Texture* texture){
    Colors color;

    for(unsigned j = 0; j < pList.size(); j++){
        vector<Country*> cList = pList[j]->getListCountry();

        for(unsigned i = 0; i < cList.size(); i++){
            int num = cList[i]->getNumberCountry();

            cList[i]->setColor(color.colorList[j]);

            Message m(PosCountries[num][0] - 5, PosCountries[num][1] - 11, to_string(cList[i]->getNumberTroop()));

            Button b(PosCountries[num][0] - 20, PosCountries[num][1] - 20, 25, color.colorList[j], texture);

            window.draw(b.circle);
            window.draw(m.text);
        }
    }
}

// cout << "test" << endl;

void testSFML(State &state) {
    vector<Player*> pList = state.getListPlayers();

    // create the window
    RenderWindow window(sf::VideoMode(1280, 986), "My window", Style::Titlebar);

    Texture t, circle;    
    
    circle.loadFromFile("res/button.png");
    circle.setSmooth(true);
    t.loadFromFile("res/carte.png");

    Sprite background(t);

    Scene scene(&window);

    scene.setListcountry(v_listcountry);
    scene.init(pList, &circle);

    Country *c_country, *d_country; // les pays attaquants et defensifs
    Country *t_country; // le pays a ajouter des troups;

    int status = 0; // afin de forcer les ordres des commandes.
    bool next = false; // indiquer si le jouer a fait l'attack, si le joueur a fait au moins un attack, il peut passer le tour a le joueur suivant,
                       // sinon il ne peut pas passer.
    bool getTroop = false; // chaque joueur ne doit que prendre le bonus de troup une fois chaque tour.
    int n_player = 0; // le chiffre player est d'indiquer que c'est le tour de quel player.
    int bonus_troop; // le nombre de troop gagner chaque tour.

    Color color;

    Message m1(1150, 25, "X : "), 
            m2(1150, 50, "Y : "), 
            m3(600, 865, "You choose the country ", NO_DISPLAY), 
            m4(600, 900, "You will attack the country ", NO_DISPLAY), 
            m5(600, 935, "If you want to attack, please press T, if not, press F ", NO_DISPLAY),
            m6(50, 900, "It's the country "),
            m7(50, 935, "Number of country is "),
            m8(600, 50, "Turn : "),
            m9(600, 10, "It's your turn player"),
            m10(40, 35, "Press P to end your turn", NO_DISPLAY),
            m11(50, 865, "You have ", NO_DISPLAY);

    scene.addListMessage({&m1, &m2, &m3, &m4, &m5, &m6, &m7, &m8, &m9, &m10, &m11});

    // run the program as long as the window is open
    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);

        Player* player = pList[n_player];
        // choisir un player par hazard pour tester
        m8.setintMessage(state.turn + 1);
        m9.setintMessage(n_player + 1);

        Event mouse;
        while (window.pollEvent(mouse))
        {
            if(!getTroop){
                bonus_troop = player->continentBonusTroop();
                m11.setintMessage(bonus_troop);
                m11.addMessage(" troops in this turn");
                getTroop = true;
            }
            if (mouse.type == Event::Closed)
                window.close();
            if (mouse.type == Event::MouseButtonPressed)
                if (mouse.key.code == Mouse::Left) 
                {
                    // placec_country->addNumberTroop(1);
                    cout << "test" << endl;
                    if(status == 0){
                        t_country = scene.findCountry(pos);
                        m11.setintMessage(bonus_troop);
                        m11.addMessage(" troops now");
                        if(player->existCountry(*t_country)){
                            t_country->addNumberTroop(1);
                            bonus_troop--;
                        }
                        if(bonus_troop == 0){
                            status++;
                            m11.show(NO_DISPLAY);
                        }
                    }
                    // choose the attack country
                    else if(status == 1)
                    {
                        player->winAttack = false;
                        m5.show(NO_DISPLAY);
                        c_country = scene.findCountry(pos);
                        if(scene.existCountry(pos)){
                            if(player->existCountry(*c_country)){
                                m3.setstrMessage(c_country->getNameCountry());    
                                status++;
                            }
                            else{
                                m3.replaceMessage("you need choose your own country !");
                            }
                        }
                    }
                    // choose the defend country
                    else if(status == 2){
                        d_country = scene.findCountry(pos);
                        if(scene.existCountry(pos)){
                            if(c_country->isAdjacent(d_country->getNumberCountry()) == true){
                                if(player->existCountry(*d_country)){
                                    m4.replaceMessage("you need choose your opponent's country !");
                                }
                                else{
                                    m4.setstrMessage(d_country->getNameCountry());
                                    status++; 
                                }
                            }
                            else{
                                m4.replaceMessage("you need choose a country adjacent !");
                            }
                        }
                    }
                    // a faire 
                }
                else if (mouse.key.code == Mouse::Right) 
                {
                    if(player->winAttack){
                        d_country->addNumberTroop(1);
                        c_country->reduceNumberTroop(1);
                    }
                    if(status == 2)
                        status = 1;
                }
        }
        if (status == 3){
            m5.show(DISPLAY);
            if(Keyboard::isKeyPressed(Keyboard::T))
            {
                int win = player->attack(c_country, d_country);
                if(win == 1){
                    Player* p = state.belongsto(d_country);
                    p->deleteCountry(d_country);
                    player->addCountry(d_country);
                    player->winAttack = true;
                    m5.replaceMessage("Click right key to add the troop in your new country");
                }
                else{
                    m5.show(NO_DISPLAY);
                }
                status = 1;
                next = true;

                m3.show(NO_DISPLAY);
                m4.show(NO_DISPLAY);
                m10.show(DISPLAY);
            }
            else if(Keyboard::isKeyPressed(Keyboard::F))
            {
                status = 1;
                m3.show(NO_DISPLAY);
                m4.show(NO_DISPLAY);
                m5.show(NO_DISPLAY);
            }
        }
        if(next){
            if(Keyboard::isKeyPressed(Keyboard::P)){
                n_player++;
                if(n_player == pList.size()){
                    n_player = 0;
                    state.turn++;
                }
                status = 0;
                next = false;
                getTroop = false;
                m10.show(NO_DISPLAY);
            }
        }

        m1.setintMessage(pos.x);
        m2.setintMessage(pos.y);
        m6.setstrMessage(scene.const_findCountry(pos).getNameCountry());
        m7.setintMessage(scene.const_findCountry(pos).getNumberCountry());

        window.clear(Color::White);	
        window.draw(background);

        scene.display_message();

        display(window, pList, &circle);

        window.display();
    }
}

// Fin test SFML

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
    v_listcountry = state.getListCountires();  

//**************************************//
    testSFML(state);
//**************************************//

//jouer
    // while(1){
    //     cout << "s" << endl;
    //     for(vector<Player>::iterator it = pList.begin(); it != pList.end(); ++it){
    //         jouer(*it);
    //     }
    // }

}

int main(int argc,char* argv[])
{
    testgame();
    //testgame();

    return 0;
}
