#include "Game.h"

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

#define LEFT 0
#define RIGHT 1

#define PLACE 0
#define ATTACK 1
#define REINFORCE 2

#define ATTACK_A 1
#define ATTACK_D 2
#define REINFORCE_M 3
#define REINFORCE_N 4
#define DISTRIBUTE 5
#define USECARD 6
#define SOLO_ATTACK 7
#define DOUBLE_ATTACK 8
#define MULTI_ATTACK 9

// Activer ou desactiver les commentaire
// #define DEBUG 1

using namespace std;
using namespace state;
using namespace sf;
using namespace render;
using namespace engine;
using namespace ai;


// TO-DO : Clean all this make them attributes

// La liste de pays recupere dans le state
vector<shared_ptr<state::Country>> v_listcountry;
// La liste de carte recupere dans le state
vector<shared_ptr<state::Card>> v_listcard;
// La liste de player recupere dans le state
vector<shared_ptr<state::Player>> pList;
// Le joueur actuel
shared_ptr<state::Player> player = make_shared<state::Player>();

//shared_ptr<ai::Ai> bot = make_shared<ai::Ai>();
shared_ptr<ai::EasyAi> easyBot = make_shared<ai::EasyAi>();
shared_ptr<ai::NormalAi> normalBot = make_shared<ai::NormalAi>();
shared_ptr<ai::HardAi> hardBot = make_shared<ai::HardAi>();
// Le pays que le joueur choisi pendant son tour
// Et le pays a et d est pour sauvegarder les deux pays que le joueurs a choisi pour qu'il puisse deplacer le troop
shared_ptr<state::Country> country, country_a, country_d;
// Le nombre de bonus troop recupere chaque tour
int bonus_troop;
// Le status correspond trois evenement : place, attack et reinforce
int status = 0;
// Des qu'on passe le joueur suivant, il faut reinitialiser le bonus troop et les status, donc il faut un parametre initPlayer 
// pour dire s'il est initialise
bool initPlayer = false;

// Les quatre chiffre pour indiquer si le pays est choisi
int attack_a = 0, attack_d = 0, attack_win = 0, reinforce_m = 0, reinforce_n = 0;

// Un boolean pour indiquer si le player a fait au moins une fois attack dans son tour, si c'est fait, il va obtenir une carte
bool attacked = false; 

// Difficultes
int difficulty = 0;

// Des messages pour etre affiche dans le gameMenu
Message *m1, *m2, *m3, *m4, *m5, *m6, *m7, *m8, *m9;

namespace render{

Game::Game(){
    this->window = new RenderWindow(sf::VideoMode::getDesktopMode(), "RISK !", Style::Titlebar|Style::Close|Style::Fullscreen);
}

Game::~Game(){
    
}

void Game::reinforce_event(){
    if(player->existCountry(*country)){
        if(reinforce_m == 0){
            reinforce_m = engine.execute(REINFORCE_M);
            gameScene.displayCircle(country, 0);
        }   
        else{
            reinforce_n = engine.execute(REINFORCE_N);
            gameScene.displayCircle(country, 1);
        }
    }
}

void Game::attack_event(){
    attacked = false;

    if(player->existCountry(*country)){
        attack_a = engine.execute(ATTACK_A);
        country_a = country;
        gameScene.displayCircle(country_a, 0);
    }
    else if(attack_a == 1){
        attack_d = engine.execute(ATTACK_D);
        country_d = country;
        gameScene.displayCircle(country_d, 1);
    }
}


void Game::place_event(){
    if(bonus_troop > 0 && player->existCountry(*country)){
        engine.execute(PLACE);
        bonus_troop--;
    }
}

/**
 * @brief Change the state for the country event
*/
void Game::change_status(){
    status = (status < 2) ? (status + 1) : status;
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
    attack_a = 0, attack_d = 0, reinforce_m = 0, reinforce_n = 0;
    initPlayer = true;
}

/**
 * @brief Init the menu before opening the window
*/
void Game::init_menu(){
    menuScene.init_main();
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
    pList = state->getPlayersList();
    v_listcountry = state->getCountriesList();
    v_listcard = state->getCardsList();
}

/**
 * @brief The event of the menu scene when the client use the mouse
*/
void Game::menuScene_event(int button){
    if(button == LEFT){
        if(menuScene.getNameMenu(pos) == "Start"){
            init_state();
    #ifdef DEBUG
            std::cout << "state init !" << std::endl;
    #endif
            gameScene.setCountriesList(v_listcountry);
            gameScene.init(pList);
            menuScene.close();
            gameScene.open();
        }
        else if(menuScene.getNameMenu(pos) == "Option")
            menuScene.init_option();
        else if(menuScene.getNameMenu(pos) == "Quit")
            window->close();
        else if(menuScene.getNameMenu(pos) == "Rule")
            menuScene.init_rule();
        else if(menuScene.getNameMenu(pos) == "About")
            system("xdg-open https://github.com/jdjenontin/plt/blob/master/README.md");
        else if(menuScene.getNameMenu(pos) == "Back")
            menuScene.init_main();
        else if(menuScene.getNameMenu(pos) == "AddHuman"){
            state->addPlayer();
            menuScene.addplayer();
        }
        else if(menuScene.getNameMenu(pos) == "DeleteHuman"){
            state->deletePlayer();
            menuScene.deleteplayer();
        }
        else if(menuScene.getNameMenu(pos) == "AddBot"){
            state->addBot(difficulty);
            menuScene.addbotplayer(difficulty);
        }
        else if(menuScene.getNameMenu(pos) == "DeleteBot"){
            state->deleteBot(difficulty);
            menuScene.deletebotplayer(difficulty);
        }
        else if(menuScene.getNameMenu(pos) == "Difficulty:"){
            difficulty++;
            if(difficulty > 2) difficulty = 0;
            menuScene.changeDifficulty(difficulty);
        }
    }
    else if(button == RIGHT){

    }
}

void Game::gameMenuEvent(){
    if(abs(pos.x - 1735) < 185 && abs(pos.y - 960) < 40){
        change_status();
    }
    else if(abs(pos.x - 1735) < 185 && abs(pos.y - 1040) < 40){
        reinforce_m = 0, reinforce_n = 0;
        state->ChangePlaying();
        engine.execute(DISTRIBUTE);
        status = 0;
        initPlayer = false;
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
        else{
            attack_a = 0, attack_d = 0, attack_win = 0;
            gameScene.displayCircle(country_a, -1);
        }
        gameMenuEvent();
    }
    else if(button == RIGHT){
        if(status == ATTACK && attack_a == 1 && attack_d == 1 && attack_win == 1 && country_a->getNumberOfTroop() > 1){
            country_a->reduceTroop(1);
            country_d->addTroop(1);
        }
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
            engine.execute(USECARD);
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
    if(Keyboard::isKeyPressed(Keyboard::R)){
        if(attack_a == 1 && attack_d == 1 && attacked == false){
            attacked = true;
            attack_win = engine.execute(SOLO_ATTACK);
        }
    }
    if(Keyboard::isKeyPressed(Keyboard::S)){
        if(attack_a == 1 && attack_d == 1 && attacked == false){
            attacked = true;
            attack_win = engine.execute(DOUBLE_ATTACK);
        }
    }
    if(Keyboard::isKeyPressed(Keyboard::T)){
        if(attack_a == 1 && attack_d == 1 && attacked == false){
            attacked = true;
            attack_win = engine.execute(MULTI_ATTACK);
        }
    }
    if(Keyboard::isKeyPressed(Keyboard::P))
        engine.execute(DISTRIBUTE);
    if(Keyboard::isKeyPressed(Keyboard::M))
        delay += 500;
    if(Keyboard::isKeyPressed(Keyboard::N))
        delay = (delay > 0) ? (delay - 500) : 0;
    if(Keyboard::isKeyPressed(Keyboard::Q)){
        initPlayer = false;
        status = 0;
        state->clear();
        menuScene.clear();
        gameScene.close();
        menuScene.open();
    } 
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
            if ((int) mouse->key.code == (int) Mouse::Left)
                leftMouse_event();
            if ((int) mouse->key.code == (int) Mouse::Right)
                rightMouse_event();
        }
    }
}

void Game::updateMessage(){
    m2->setstrMessage(player->getName());
    switch (status)
    {
    case PLACE:
    m6->setstrMessage("Place");
    m7->setintMessage(bonus_troop);
    m7->addMessage(" troops now");
        break;
    case ATTACK:
    m6->setstrMessage("Attack");
    if(attack_a == 1 && attack_d == 1 && attacked == false && country_a->getNumberOfTroop() > 1){
        m8->setintMessage(AttackComputer::victoryProba(country_a->getNumberOfTroop()-1, country_d->getNumberOfTroop())*100);
        m8->addMessage("%");
    }
        break;
    case REINFORCE:
    m6->setstrMessage("Reinforce");
    default:
        break;
    }
}

void Game::createMessage(){
    m1 = new Message(1570, 30, "Turn : ");
    m2 = new Message(1570, 90, "It's your turn : ");
    m3 = new Message(1570, 150, "Player list : ");
    m4 = new Message(1640, 940, "Next Phase");
    m5 = new Message(1650, 1020, "End Turn");
    m6 = new Message(1570, 510, "You are doing : ");
    m7 = new Message(1570, 570, "You have ");
    m8 = new Message(1570, 630, "Your win rate is : ");
    m9 = new Message(1570, 690, "Player ", NO_DISPLAY);

    m1->setSize(30);
    m2->setSize(30);
    m3->setSize(30);
    m4->setSize(35);
    m5->setSize(35);
    m6->setSize(30);
    m7->setSize(30);
    m8->setSize(30);
    m9->setSize(35);
    gameScene.addListMessage({m1, m2, m3, m4, m5, m6, m7, m8, m9});
}

void Game::aiProcess(){
    if(player->getType() == EASYBOT){
        easyBot->setState(state);
        easyBot->execute(player);
    }
    else if(player->getType() == NORMALBOT){
        normalBot->setState(state);
        normalBot->execute(player);
    }
    else if(player->getType() == HARDBOT){
        hardBot->setState(state);
        hardBot->execute(player);
    }
    state->ChangePlaying();
    engine.execute(DISTRIBUTE);
    status = 0;
    initPlayer = false;
}

/**
 * @brief The process for the game scene
*/
void Game::game_process(){
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    player = pList[state->getOrderPlayer()];
    engine.setPlayer(player);
    m1->setintMessage(state->getTurn() + 1);

    if(player->getCountriesList().size() == 42){
        m9->show(DISPLAY);
        m9->setstrMessage(player->getName());
        m9->addMessage(" win !");
    }
    else{
        if(player->getType() != HUMAN) aiProcess();
        else{
            updateMessage();
            if(!initPlayer) init_player();
        }
    }
}

/**
 * @brief Open the window
*/
void Game::window_begin(){
    Event mouse;
    createMessage();

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

void Game::setState (std::shared_ptr<state::State>& state){
    this->state = state;
}

void Game::setPlayer(int humans, std::vector<int> bots){
    if(humans >= 2){
        for(int i = 0; i < (humans - 2); i++)
            state->addPlayer();
    }
    else if(humans == 1)
        state->deletePlayer();
    else{
        state->deletePlayer();
        state->deletePlayer();
    }

    for(int i = 0; i < bots[0]; i++){
        state->addBot(Difficulty::EASY);
    }
    for(int i = 0; i < bots[1]; i++){
        state->addBot(Difficulty::NORMAL);
    }
    for(int i = 0; i < bots[2]; i++){
        state->addBot(Difficulty::HARD);
    }
}

void Game::setDelay(int m_delay){
    delay = m_delay;
}

/**
 * @brief Init the menu and start the game
*/
void Game::begin(TypeScene scene){
    if(scene == TypeScene::MENU){
        init_menu();
        engine.init(state);
        window_begin();
    }
    else if(scene == TypeScene::GAME){
        init_menu();
        engine.init(state);
        init_state();
        gameScene.setCountriesList(v_listcountry);
        gameScene.init(pList);
        menuScene.close();
        gameScene.open();
        window_begin();
    }
    
}

}