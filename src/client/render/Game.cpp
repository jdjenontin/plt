#include "Game.h"

#include <iostream>

#define LEFT 0
#define RIGHT 1

#define PLACE 0
#define ATTACK 1
#define REINFORCE 2
#define DISTRIBUTE 5
#define USECARD 6

#define ATTACK_A 1
#define ATTACK_D 2
#define REINFORCE_M 3
#define REINFORCE_N 4

// Activer ou desactiver les commentaire
#define DEBUG 1

using namespace std;
using namespace state;
using namespace sf;
using namespace render;
using namespace engine;
using namespace ai;

vector<Country*> v_listcountry;
vector<state::Card*> v_listcard;
vector<Player*> pList;
Player* player;
Country* country;
int bonus_troop;
int status = 0;
bool initPlayer = false;

namespace render{

Game::Game(){
    this->window = new RenderWindow(sf::VideoMode::getDesktopMode(), "RISK !", Style::Titlebar|Style::Close|Style::Fullscreen);
}

Game::~Game(){

}

void Game::reinforce_event(){
    static int m = 0, n = 0;

    if(player->existCountry(*country)){
        if(m == 0)   m = engine.execute(REINFORCE_M);
        else    n = engine.execute(REINFORCE_N);
    }
}

void Game::attack_event(){
    int a = 0, d = 0;

    if(player->existCountry(*country))
        a = engine.execute(ATTACK_A);
    else
        d = engine.execute(ATTACK_D);
}


void Game::place_event(){
    if(bonus_troop > 0 && player->existCountry(*country)){
        int s = engine.execute(PLACE);
        bonus_troop--;
    }
}

/**
 * @brief Change the state for the country event
*/
void Game::change_status(){
    status = (status < 7) ? (status + 1) : 0;
}

/**
 * @brief The event of the country when the client choose the country using the mouse
*/
void Game::country_event(){
#ifdef DEBUG
    cout << "dans la fonction :" << __func__ << "avec status :" << status << endl;
#endif
    engine.setCountry(country);
    switch (status)
    {
    case PLACE:
    place_event();
        break;
    case ATTACK:
    attack_event();
        break;
    case REINFORCE:
    reinforce_event();
        break;           
    default:
        break;
    }
}

/**
 * @brief Init the player for getting the bonus of troop
*/
void Game::init_player(){
    bonus_troop = player->continentBonusTroop();
    initPlayer = true;
}

/**
 * @brief Init the menu before opening the window
*/
void Game::init_menu(){
    menuScene.init();
    menuScene.setWindow(window);
}

/**
 * @brief Init the card before opening the card scene
*/
void Game::init_card(){
    cardScene.setWindow(window);
    cardScene.setPlayer(player);
    cardScene.init();
}

/**
 * @brief Init the state before the start of the game
*/
void Game::init_state(){
    gameScene.setWindow(window);
    state->init();
    pList = state->getListPlayers();
    v_listcountry = state->getListCountires();
    v_listcard = state->getListCard();
}

/**
 * @brief The event of the menu scene when the client use the mouse
*/
void Game::menuScene_event(int button){
    if(button == LEFT){
        if(menuScene.getNameMenu(pos) == "start"){
            init_state();
    #ifdef DEBUG
            std::cout << "state init !" << std::endl;
    #endif
            gameScene.setListcountry(v_listcountry);
            gameScene.init(pList);
            menuScene.close();
            gameScene.open();
        }
        else if(menuScene.getNameMenu(pos) == "addplayer"){
            if(state->numberPlayer + state->numberBot < 5){
                state->numberPlayer++;
                menuScene.addplayer();
            }
        }
        else if(menuScene.getNameMenu(pos) == "deleteplayer"){
            if(state->numberPlayer > 1){
                state->numberPlayer--;
                menuScene.deleteplayer();
            } 
        }
        else if(menuScene.getNameMenu(pos) == "addbot"){
            if(state->numberPlayer + state->numberBot < 5){
                state->numberBot++;
                menuScene.addbotplayer();
            }
        }
        else if(menuScene.getNameMenu(pos) == "deletebot"){
            if(state->numberBot > 0){
                state->numberBot--;
                menuScene.deletebotplayer();
            }
        }
    }
    else if(button == RIGHT){

    }
}

/**
 * @brief The event of the game scene when the client use the mouse
*/
void Game::gameScene_event(int button){
    if(button == LEFT){
        if(gameScene.isCardButton(pos)){
            init_card();
            gameScene.close();
            cardScene.open();
        }
        country = gameScene.findCountry(pos);
        if(country)
            country_event();
    }
    else if(button == RIGHT){
        // For test 
        change_status();
    }
}

/**
 * @brief The event of the card scene when the client use the mouse
*/
void Game::cardScene_event(int button){
    if(button == LEFT){
        if(cardScene.isGameButton(pos)){
            cardScene.close();
            gameScene.open();
        }
        if(cardScene.isChangeButton(pos) && status == 0){
            int s = engine.execute(USECARD);
            cardScene.init();
            bonus_troop += engine.getBonus_troop();
        }
    }
    else if(button == RIGHT){

    }
}

/**
 * @brief The event when the client use the keyboard
*/
void Game::key_event(){

}

/**
 * @brief The event when the client use the right button of mouse
*/
void Game::rightMouse_event(){
    if(menuScene.isOpen())
        menuScene_event(RIGHT);
    else if(gameScene.isOpen())
        gameScene_event(RIGHT);
    else if(cardScene.isOpen())
        cardScene_event(RIGHT);
}

/**
 * @brief The event when the client use the left button of mouse
*/
void Game::leftMouse_event(){
    if(menuScene.isOpen())
        menuScene_event(LEFT);
    else if(gameScene.isOpen())
        gameScene_event(LEFT);
    else if(cardScene.isOpen())
        cardScene_event(LEFT);
}

/**
 * @brief The event when the client use the mouse
*/
void Game::mouse_event(Event* mouse){
    while(window->pollEvent(*mouse))
    {
        if (mouse->type == Event::Closed)
            window->close();
        if (mouse->type == Event::MouseButtonPressed){
            if (mouse->key.code == Mouse::Left)
                leftMouse_event();
            if (mouse->key.code == Mouse::Right)
                rightMouse_event();
        }
    }
}

/**
 * @brief The process for the game scene
*/
void Game::game_process(){
    player = pList[state->getOrderPlayer()];
    engine.setPlayer(player);
    if(!initPlayer) init_player();
}

/**
 * @brief Open the window
*/
void Game::window_begin(){
    Event mouse;
    engine.init(state);

    while(window->isOpen())
    {
        pos = Mouse::getPosition(*window);

        if(gameScene.isOpen())
            game_process();
        //Evenement du souris
        mouse_event(&mouse);
        //Evenement du clavier
        key_event();

        if(gameScene.isOpen())
            gameScene.display();
        else if(cardScene.isOpen())
            cardScene.display();
        else if(menuScene.isOpen())
            menuScene.display();

        window->display();
    }
}

void Game::setState(State* state){
    this->state = state;
}

/**
 * @brief Init the menu and start the game
*/
void Game::begin(){
    init_menu();
    window_begin();
}

}