#include "MenuScene.h"

#include <iostream>
#include <vector>

#define X_MENU 950
#define Y_MENU 500

#define EASY 0
#define NORMAL 1
#define HARD 2

#define DEBUG 1

namespace render {

int plist_size = 2;
std::vector<int> blist_size(3, 0);

Colors color;

sf::Texture* c = new sf::Texture();
sf::Texture back, logo;
sf::Sprite s_back, s_logo;

std::vector<std::string> listname = {"Tom", "Bob", "Uriel", "Sam", "Yann"};

MenuScene::MenuScene () {
    sf::Vector2f pos_logo(680, 140);

    isopen = true;
    back.loadFromFile("res/menubackground.jpg");
    s_back.setTexture(back);
    logo.loadFromFile("res/risk_logo.png");
    s_logo.setTexture(logo);
    s_logo.setPosition(pos_logo);
    c->loadFromFile("res/button.png");
    c->setSmooth(true);
}

MenuScene::~MenuScene () {

}

void MenuScene::createListMain(){
    Menu start(X_MENU, Y_MENU, "Start");
    listMenu.push_back(start);

    Menu option(X_MENU, Y_MENU+100, "Option");
    listMenu.push_back(option);

    Menu rule(X_MENU, Y_MENU+200, "Rule");
    listMenu.push_back(rule);

    Menu about(X_MENU, Y_MENU+300, "About");
    listMenu.push_back(about);

    Menu quit(X_MENU, Y_MENU+400, "Quit");
    listMenu.push_back(quit);
}

void MenuScene::createListOption(){
    static sf::Texture t_list, t_add, t_del, t_back, t_choose;
    t_list.loadFromFile("res/gamer.png");
    t_add.loadFromFile("res/add.png");
    t_del.loadFromFile("res/delete.png");
    t_back.loadFromFile("res/arrow.png");
    t_choose.loadFromFile("res/choose.png");

    for(int i = 0; i < 6; i++){
        if(i%2 == 0){
            Menu m(X_MENU-275, Y_MENU+150*(i/2+1), 400, 100, &t_list, " ");
            listMenu.push_back(m);
        }
        else{
            Menu m(X_MENU+275, Y_MENU+150*(i/2+1), 400, 100, &t_list, " ");
            listMenu.push_back(m);
        }
    }

    Menu add_human(X_MENU-275, Y_MENU, 50, 50, &t_add, " ");
    add_human.addMessage(X_MENU-240, Y_MENU-20, 30, "AddHuman", sf::Color::White);
    listMenu.push_back(add_human);
    Menu add_bot(X_MENU-275, Y_MENU+50, 50, 50, &t_add, " ");
    add_bot.addMessage(X_MENU-240, Y_MENU+30, 30, "AddBot", sf::Color::White);
    listMenu.push_back(add_bot);
    Menu del_human(X_MENU, Y_MENU, 50, 50, &t_del, " ");
    del_human.addMessage(X_MENU+35, Y_MENU-20, 30, "DeleteHuman", sf::Color::White);
    listMenu.push_back(del_human);
    Menu del_bot(X_MENU, Y_MENU+50, 50, 50, &t_del, " ");
    del_bot.addMessage(X_MENU+35, Y_MENU+30, 30, "DeleteBot", sf::Color::White);
    listMenu.push_back(del_bot);
    Menu back(X_MENU+275, Y_MENU, 50, 50, &t_back, " ");
    back.addMessage(X_MENU+310, Y_MENU-20, 30, "Back", sf::Color::White);
    listMenu.push_back(back);
    Menu choose(X_MENU+275, Y_MENU+50, 50, 50, &t_choose, " ");
    choose.addMessage(X_MENU+310, Y_MENU+30, 30, "Difficulty:", sf::Color::White);
    listMenu.push_back(choose);
}

void MenuScene::addMessage(int x, int y, int size, std::string message, sf::Color color){
    Message m(x, y, message);
    m.setColor(color);
    m.setSize(size);
    window->draw(m.text);
}

void MenuScene::clearList(){
    listMenu.clear();
}

void MenuScene::init_main () {
    option_isOpen = false;
    main_isOpen = true;
    clearList();

    createListMain();
}

void MenuScene::init_option(){
    option_isOpen = true;
    main_isOpen = false;
    clearList();

    createListOption();
}

void MenuScene::initList(){
    for(int i = 0; i < plist_size; i++){
        if(i%2 == 0){
            addMessage(X_MENU-300, Y_MENU-20+150*(i/2+1), 30, listname[i], color.colorList[i]);}
        else{
            addMessage(X_MENU+250, Y_MENU-20+150*(i/2+1), 30, listname[i], color.colorList[i]);
        }    
    }
    for(int i = 0; i < blist_size[EASY]; i++){
        int size = i+plist_size;
        if((size)%2 == 0)
            addMessage(X_MENU-315, Y_MENU-20+150*((size)/2+1), 30, "EasyBot", color.colorList[size]);
        else
            addMessage(X_MENU+235, Y_MENU-20+150*((size)/2+1), 30, "EasyBot", color.colorList[size]);
    }
    for(int i = 0; i < blist_size[NORMAL]; i++){
        int size = i+blist_size[EASY]+plist_size;
        if((size)%2 == 0)
            addMessage(X_MENU-325, Y_MENU-20+150*((size)/2+1), 30, "NormalBot", color.colorList[size]);
        else
            addMessage(X_MENU+225, Y_MENU-20+150*((size)/2+1), 30, "NormalBot", color.colorList[size]);
    }
    for(int i = 0; i < blist_size[HARD]; i++){
        int size = i+blist_size[EASY]+blist_size[NORMAL]+plist_size;
        if((size)%2 == 0)
            addMessage(X_MENU-315, Y_MENU-20+150*((size)/2+1), 30, "HardBot", color.colorList[size]);
        else
            addMessage(X_MENU+235, Y_MENU-20+150*((size)/2+1), 30, "HardBot", color.colorList[size]);
    }
    switch (difficulty)
    {
    case EASY:
    addMessage(X_MENU+440, Y_MENU+30, 30, "Easy", sf::Color::White);
        break;
    case NORMAL:
    addMessage(X_MENU+440, Y_MENU+30, 30, "Normal", sf::Color::White);
        break;
    case HARD:
    addMessage(X_MENU+440, Y_MENU+30, 30, "Hard", sf::Color::White);
        break;
    default:
        break;
    }
}

std::string MenuScene::getNameMenu (sf::Vector2i pos) {
    if(main_isOpen){
        for(auto m : listMenu){
            if(abs(pos.x - m.getPostion().x) < 100 && abs(pos.y - m.getPostion().y) < 25){
                return m.getName();
            }
        }
    }
    else if(option_isOpen){
        for(auto m : listMenu){
            if(abs(pos.x - m.getPostion().x) < 25 && abs(pos.y - m.getPostion().y) < 25){
                return m.getName();
            }
        }
    }
    return "";
}

void MenuScene::addplayer (){
    plist_size++;
}

void MenuScene::addbotplayer (int difficulty){
    if(plist_size+blist_size[EASY]+blist_size[NORMAL]+blist_size[HARD] < 5)
        blist_size[difficulty]++;
}

void MenuScene::deleteplayer (){
    plist_size--;
}

void MenuScene::deletebotplayer (int difficulty){
    if(blist_size[difficulty] != 0)
        blist_size[difficulty]--;
}

void MenuScene::changeDifficulty(int difficulty){
    this->difficulty = difficulty;
}

void MenuScene::display () {
    window->clear(sf::Color::White);
    window->draw(s_back);
    window->draw(s_logo);
    for(auto m : listMenu)
        display_menu(m);
    
    if(option_isOpen)
        initList();
}

void MenuScene::display_menu (Menu menu) {
    sf::RectangleShape rect = menu.getRectangle();

    window->draw(rect);
    window->draw(menu.getMessage()->text);
}

}