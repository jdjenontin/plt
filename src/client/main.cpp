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
#include <engine.h>

using namespace std;
using namespace state;
using namespace sf;
using namespace render;
using namespace engine;

vector<Country*> v_listcountry;
// cout << "test" << endl;

void testSFML(State &state) {
    vector<Player*> pList = state.getListPlayers();

    // create the window
    RenderWindow window(sf::VideoMode(1280, 986), "My window", Style::Titlebar);

    Texture circle;    
    
    circle.loadFromFile("res/button.png");
    circle.setSmooth(true);

    Scene scene(&window);

    scene.setListcountry(v_listcountry);
    scene.init(pList, &circle);

    int status = 0; // afin de forcer les ordres des commandes.
    bool next = false; // indiquer si le jouer a fait l'attack, si le joueur a fait au moins un attack, il peut passer le tour a le joueur suivant,
                       // sinon il ne peut pas passer.
    bool getTroop = false; // chaque joueur ne doit que prendre le bonus de troup une fois chaque tour.

    // les trois commandes executables
    Place place;
    Attack attack;
    Reinforce reinforce; 

    attack.setState(&state);

    // mettre des messages dans la fenetre
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

    // et ajouter des messages dans la liste pour l'afficher
    scene.addListMessage({&m1, &m2, &m3, &m4, &m5, &m6, &m7, &m8, &m9, &m10, &m11});

    // run the program as long as the window is open
    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);

        Player* player = pList[state.getNumberPlayer()];
        // choisir un player par hazard pour tester
        m8.setintMessage(state.getTurn() + 1);
        m9.setintMessage(state.getNumberPlayer() + 1);

        place.setPlayer(player);
        attack.setPlayer(player);
        reinforce.setPlayer(player);

        Event mouse;
        while (window.pollEvent(mouse))
        {
            // recuperer le bonus de troup
            // une fois le bonus de troup est recuperer, on ne rentre plus dans ce boucle jusqu'a le prochain joueur
            if(!getTroop){
                if(state.getNumberPlayer() == pList.size() - 1)
                    place.bonus_troop = player->continentBonusTroop() + 1;
                else
                    place.bonus_troop = player->continentBonusTroop();
                m11.setintMessage(place.bonus_troop);
                m11.addMessage(" troops in this turn");
                getTroop = true;
            }
            if (mouse.type == Event::Closed)
                window.close();
            // appuyer sur le souris 
            if (mouse.type == Event::MouseButtonPressed)
                // appuyer sur le gauche
                if (mouse.key.code == Mouse::Left) 
                {
                    // quand status = 0, on distribute les troups, jusqu'a le bonus troup est nul, on passe le status 1 
                    if(status == 0){
                        place.setcountry(scene.findCountry(pos));
                        place.execute();

                        m11.setintMessage(place.bonus_troop);
                        m11.addMessage(" troops now");
                        if(place.bonus_troop == 0){
                            status++;
                            m11.show(NO_DISPLAY);
                        }
                    }
                    // choose the attack country, et inplementer le status
                    else if(status == 1)
                    {
                        m5.show(NO_DISPLAY);
                        attack.setc_country(scene.findCountry(pos));
                        if(scene.existCountry(pos)){
                            if(attack.existC_country()){
                                if(attack.abletoattack()){
                                    m3.setstrMessage(scene.findCountry(pos)->getNameCountry());    
                                    status++;
                                }
                                else
                                    m5.replaceMessage("you need choose a country with more than 1 troop");
                            }
                            else{
                                m3.replaceMessage("you need choose your own country !");
                            }
                        }
                    }
                    // choose the defend country, et inplementer le status
                    else if(status == 2){
                        attack.setd_country(scene.findCountry(pos));
                        if(scene.existCountry(pos)){
                            if(attack.isadjacent()){
                                if(attack.existD_country()){
                                    m4.replaceMessage("you need choose your opponent's country !");
                                }
                                else{
                                    m4.setstrMessage(scene.findCountry(pos)->getNameCountry());
                                    status++; 
                                }
                            }
                            else{
                                m4.replaceMessage("you need choose a country adjacent !");
                            }
                        }
                    }
                    else if(status == 4){
                        // m_country = scene.findCountry(pos);
                        // if(scene.existCountry(pos)){
                        //     if(player->existCountry(*c_country)){
                        //         m3.setstrMessage(c_country->getNameCountry());    
                        //         status++;
                        //     }
                        //     else{
                        //         m3.replaceMessage("you need choose your own country !");
                        //     }
                        // }
                    }
                    else if(status == 5){

                    }
                    // a faire 
                }
                else if (mouse.key.code == Mouse::Right) 
                {
                    // si le joueur gagne, il peut bouger ses troup en utilisant le bouton a droit
                    if(player->winAttack){
                        attack.movetroop();
                    }
                    // si le joueur veut rechoisir le pays attaquant, il peut utiliser le bouton a droit
                    if(status == 2)
                        status = 1;
                    if(status == 3)
                        status = 4;
                }
        }
        if (status == 3){
            m5.show(DISPLAY);
            // appuyer T pour attacker
            if(Keyboard::isKeyPressed(Keyboard::T))
            {
                int win = attack.execute();
                if(win == 1){
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
            // appuyer F pour annuler
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
                state.ChangePlaying();
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

        scene.display_message();

        window.display();
    }
}

// Fin test SFML
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

}

int main(int argc,char* argv[])
{
    testgame();
    //testgame();

    return 0;
}
