#include "MenuScene.h"

#include <iostream>

#define X_MENU 950
#define Y_MENU 500

#define DEBUG 1

namespace render {

int plist_size = 2, blist_size = 0;

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
    static sf::Texture t_list, t_add, t_del, t_back;
    t_list.loadFromFile("res/gamer.png");
    t_add.loadFromFile("res/add.png");
    t_del.loadFromFile("res/delete.png");
    t_back.loadFromFile("res/arrow.png");

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
    for(int i = 0; i < blist_size; i++){
        if((i+plist_size)%2 == 0)
            addMessage(X_MENU-300, Y_MENU-20+150*((i+plist_size)/2+1), 30, "EasyBot", color.colorList[i+plist_size]);
        else
            addMessage(X_MENU+250, Y_MENU-20+150*((i+plist_size)/2+1), 30, "EasyBot", color.colorList[i+plist_size]);
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

void MenuScene::addbotplayer (){
    blist_size++;
}

void MenuScene::deleteplayer (){
    plist_size--;
}

void MenuScene::deletebotplayer (){
    blist_size--;
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