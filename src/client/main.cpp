#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <sstream>
#include <state.h>
#include <render.h>
#include <engine.h>
#include <ai.h>

using namespace std;
using namespace state;
using namespace sf;
using namespace render;
using namespace engine;
using namespace ai;

vector<Country*> v_listcountry;

vector<state::Card*> v_listcard;

void testSFML() {
    State* state = new State();

    vector<Player*> pList;

    // create the window
    RenderWindow window(sf::VideoMode::getDesktopMode(), "RISK !", Style::Titlebar|Style::Close|Style::Fullscreen);
    Texture circle;
    
    circle.loadFromFile("res/button.png");
    circle.setSmooth(true);

    GameScene gamescene(&window);

    MenuScene menuscene(&window);

    CardScene cardscene(&window);

    menuscene.init();

    int status = 0; // afin de forcer les ordres des commandes.
    int toggleAttack = 0; //Pour savoir si on peux attaquer
    bool next = false; // indiquer si le jouer a fait l'attack, si le joueur a fait au moins un attack, il peut passer le tour a le joueur suivant,
                       // sinon il ne peut pas passer.
    bool getTroop = false; // chaque joueur ne doit que prendre le bonus de troup une fois chaque tour.

    // les quatre commandes executables
    Place place;
    Attack attack;
    Reinforce reinforce; 
    DistributeCard distributecard;
    UseCard usecard;

    attack.setState(state);
    distributecard.setState(state);

    // mettre des messages dans la fenetre
    // "Press S for one attack D for two attacks  or M for Multiple attack"
    // "If you want to attack, please press A, if not, press F "
    Message m1(1150, 25, "X : "), 
            m2(1150, 50, "Y : "), 
            m3(600, 865, "You choose the country ", NO_DISPLAY), 
            m4(600, 900, "You will attack the country ", NO_DISPLAY), 
            m5(600, 935, "If you want to attack, please press A, if not, press F ", NO_DISPLAY),
            m6(50, 900, "It's the country "),
            m7(50, 935, "Number of country is "),
            m8(600, 50, "Turn : "),
            m9(600, 10, "It's your turn "),
            m10(80, 35, "Press P to end your turn", NO_DISPLAY),
            m11(50, 865, "You have ", NO_DISPLAY);

    // et ajouter des messages dans la liste pour l'afficher
    gamescene.addListMessage({&m3, &m4, &m5, &m6, &m7, &m8, &m9, &m10, &m11});

    // run the program as long as the window is open
    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);

        Player* player;

        Ai ai;

        ai.setState(state);

        if(gamescene.isOpen()){
            player = pList[state->getOrderPlayer()];
            //////////////////////////////////////////
            //espace de travail de l'IA
            if(player->getTypeplayer() == BOT){
                ai.setPlayer(player);
                ai.execute(Difficulty::EASY);

                state->ChangePlaying();
                status = 0;
            }
            ///////////////////////////////////////////

            string s = player->getName();

            m8.setintMessage(state->getTurn() + 1);
            m9.setstrMessage(s);

            place.setPlayer(player);
            attack.setPlayer(player);
            reinforce.setPlayer(player);
            distributecard.setPlayer(player);
            usecard.setPlayer(player);
        }

        Event mouse;
        while (window.pollEvent(mouse))
        {
            // recuperer le bonus de troup
            // une fois le bonus de troup est recuperer, on ne rentre plus dans cette boucle jusqu'a le prochain joueur
            if(gamescene.isOpen()){
                if(!getTroop){  
                if(state->getOrderPlayer() == (int)pList.size() - 1)
                    place.bonus_troop = player->continentBonusTroop() + 1;
                else
                    place.bonus_troop = player->continentBonusTroop();
                m11.setintMessage(place.bonus_troop);
                m11.addMessage(" troops in this turn");
                getTroop = true;
                }
            }
            
            if (mouse.type == Event::Closed)
                window.close();
            // appuyer sur le souris 
            if (mouse.type == Event::MouseButtonPressed)
                // appuyer sur le gauche
                if (mouse.key.code == Mouse::Left) 
                {
                    //l'espace de travail de cardscene
                    if(cardscene.isOpen()){
                        if(cardscene.isGameButton(pos)){
                            cardscene.close();
                            gamescene.open();
                        }
                        if(cardscene.isChangeButton(pos) && status == 0){
                            if(usecard.canUseCard()){
                                usecard.execute();
                                cardscene.init();
                                place.bonus_troop += usecard.getM_bonusTroop();
                                cout << "bonus :" << usecard.getM_bonusTroop() << endl;
                            }
                            m11.setintMessage(place.bonus_troop);
                            m11.addMessage(" troops now");
                        }
                    }

                    //l'espace de travail de gamescene
                    else if(gamescene.isOpen()){
                        if(gamescene.isCardButton(pos)){
                            player = pList[state->getOrderPlayer()];

                            cardscene.setPlayer(player);
                            cardscene.init();

                            gamescene.close();
                            cardscene.open();
                        }
                        // quand status = 0, on distribute les troups, jusqu'a le bonus troup est nul, on passe le status 1 
                        if(status == 0){
                            if(gamescene.existCountry(pos)){
                                place.setcountry(gamescene.findCountry(pos));
                                place.execute();
                            }
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
                            player->winAttack = false;

                            m5.show(NO_DISPLAY);
                            attack.setAttackCountry(gamescene.findCountry(pos));
                            if(gamescene.existCountry(pos)){
                                if(attack.existAttackCountry()){
                                    if(attack.abletoattack()){
                                        m3.setstrMessage(gamescene.findCountry(pos)->getNameCountry());    
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
                            attack.setDefCountry(gamescene.findCountry(pos));
                            if(gamescene.existCountry(pos)){
                                if(attack.isadjacent()){
                                    if(attack.existDefCountry()){
                                        m4.replaceMessage("you need choose your opponent's country !");
                                    }
                                    else{
                                        m4.setstrMessage(gamescene.findCountry(pos)->getNameCountry());
                                        status++; 
                                    }
                                }
                                else{
                                    m4.replaceMessage("you need choose a country adjacent !");
                                }
                            }
                        }
                        else if(status == 4){
                            reinforce.setm_country(gamescene.findCountry(pos));
                            if(gamescene.existCountry(pos)){
                                if(reinforce.existM_country()){
                                    m3.setstrMessage(gamescene.findCountry(pos)->getNameCountry()); 
                                    status++;
                                }
                            }
                        }
                        else if(status == 5){
                            reinforce.setn_country(gamescene.findCountry(pos));
                            if(gamescene.existCountry(pos)){
                                if(reinforce.existN_country()){
                                    reinforce.execute();
                                }
                            }
                        }
                    }

                    if(menuscene.isOpen()){
                        if(menuscene.getNameMenu(pos) == "start"){
                            state->init();

                            pList = state->getListPlayers();

                            v_listcountry = state->getListCountires();

                            v_listcard = state->getListCard();

                            gamescene.setListcountry(v_listcountry);
                            gamescene.init(pList);

                            menuscene.close();
                            gamescene.open();
                        }
                        else if(menuscene.getNameMenu(pos) == "addplayer"){
                            if(state->numberPlayer + state->numberBot < 5){
                                state->numberPlayer++;
                                menuscene.addplayer();
                            }
                        }
                        else if(menuscene.getNameMenu(pos) == "deleteplayer"){
                            if(state->numberPlayer > 1){
                                state->numberPlayer--;
                                menuscene.deleteplayer();
                            } 
                        }
                        else if(menuscene.getNameMenu(pos) == "addbot"){
                            if(state->numberPlayer + state->numberBot < 5){
                                state->numberBot++;
                                menuscene.addbotplayer();
                            }
                        }
                        else if(menuscene.getNameMenu(pos) == "deletebot"){
                            if(state->numberBot > 0){
                                state->numberBot--;
                                menuscene.deletebotplayer();
                            }
                        }
                    }
                    // a faire 
                }
                else if (mouse.key.code == Mouse::Right) 
                {
                    // si le joueur gagne, il peut bouger ses troup en utilisant le bouton a droit
                    if(gamescene.isOpen()){
                        if(player->winAttack){
                            attack.movetroop();
                        }
                        // si le joueur veut rechoisir le pays attaquant, il peut utiliser le bouton a droit
                        if(status == 2)
                            status = 1;

                        if(status == 5)
                            status = 4;
                    }
                }
        }
        if(gamescene.isOpen()){
            if(Keyboard::isKeyPressed(Keyboard::R)){
                status = 4;
                toggleAttack = 1;
            }

            if(Keyboard::isKeyPressed(Keyboard::C)){
                distributecard.execute();
            }

            if (status == 3){
                
                if (toggleAttack == 0) m5.show(DISPLAY);
                
                // appuyer T pour attacker
                //Conquered lets us know if the def country was completly defeated or not
                int conquered = 0;
                cout << toggleAttack << endl;

                if(Keyboard::isKeyPressed(Keyboard::A))
                {   
                    m5.replaceMessage("Press S for solo attack D for double attack or M for Multiple attack");
                    toggleAttack = 1;
                }


                // appuyer F pour annuler
                else if(Keyboard::isKeyPressed(Keyboard::F))
                {
                    status = 1;
                    m3.show(NO_DISPLAY);
                    m4.show(NO_DISPLAY);
                    m5.show(NO_DISPLAY);
                }

                else if(Keyboard::isKeyPressed(Keyboard::S) and toggleAttack){
                    //m5.replaceMessage("If you want to attack, please press A, if not, press F ");
                    conquered = attack.soloAttack();
                    status = 1;
                    next = true;

                    m3.show(NO_DISPLAY);
                    m4.show(NO_DISPLAY);
                    m10.show(DISPLAY);
                    toggleAttack = 0;

                    if(conquered == 1){
                        m5.replaceMessage("Click right key to add the troop in your new country");
                    }
                    else{
                        m5.show(NO_DISPLAY);
                    }
                }

                
            
                else if(Keyboard::isKeyPressed(Keyboard::D) and toggleAttack){
                    //m5.replaceMessage("If you want to attack, please press A, if not, press F ");
                    if(attack.getAttackCountry()->getNumberTroop() > 2)
                        {
                        conquered = attack.doubleAttack();
                        status = 1;
                        next = true;

                        m3.show(NO_DISPLAY);
                        m4.show(NO_DISPLAY);
                        m10.show(DISPLAY);
                        toggleAttack = 0;

                        if(conquered == 1){
                            m5.replaceMessage("Click right key to add the troop in your new country");
                        }
                        else{
                            m5.show(NO_DISPLAY);
                        }
                    }
                    else
                    {
                        m5.replaceMessage("You cannot double attack");
                    }
                }

                else if(Keyboard::isKeyPressed(Keyboard::T) and toggleAttack){
                    //m5.replaceMessage("If you want to attack, please press A, if not, press F ");
                    if(attack.getAttackCountry()->getNumberTroop() > 2)
                        {
                        conquered = attack.tripleAttack();
                        status = 1;
                        next = true;

                        m3.show(NO_DISPLAY);
                        m4.show(NO_DISPLAY);
                        m10.show(DISPLAY);
                        toggleAttack = 0;

                        if(conquered == 1){
                            m5.replaceMessage("Click right key to add the troop in your new country");
                        }
                        else{
                            m5.show(NO_DISPLAY);
                        }
                    }
                    else
                    {
                        m5.replaceMessage("You cannot triple attack");
                    }
                }

                else if(Keyboard::isKeyPressed(Keyboard::M) and toggleAttack){
                    //m5.replaceMessage("If you want to attack, please press A, if not, press F ");
                    cout << "Attack1" << endl;
                    conquered = attack.multipleAttack();
                    cout << "Attack2" << endl;
                    status = 1;
                    next = true;
                    m3.show(NO_DISPLAY);
                    m4.show(NO_DISPLAY);
                    m10.show(DISPLAY);
                    toggleAttack = 0;

                    if(conquered == 1){
                        m5.replaceMessage("Click right key to add the troop in your new country");
                    }
                    else{
                        m5.show(NO_DISPLAY);
                    }
                }
                    

                
            }

            if(next){
                if(Keyboard::isKeyPressed(Keyboard::P)){
                    state->ChangePlaying();
                    distributecard.execute();
                    status = 0;
                    next = false;
                    getTroop = false;
                    m10.show(NO_DISPLAY);
                }
            }

            m6.setstrMessage(gamescene.const_findCountry(pos).getNameCountry());
            m7.setintMessage(gamescene.const_findCountry(pos).getNumberCountry());
        }

        if(menuscene.isOpen())
            menuscene.display();
        else if(gamescene.isOpen())
            gamescene.display();
        else if(cardscene.isOpen())
            cardscene.display();

        m1.setintMessage(pos.x);
        m2.setintMessage(pos.y);

        window.draw(m1.text);
        window.draw(m2.text);

        window.display();
    }
}

int main(int argc,char* argv[])
{
    srand((unsigned) time(NULL));
    testSFML();
    return 0;
}
