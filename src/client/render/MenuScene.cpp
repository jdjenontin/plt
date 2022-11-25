#include "MenuScene.h"

#include <iostream>

namespace render {

int plist_size = 2;

Colors color;

sf::Texture* c = new sf::Texture();

std::vector<std::string> listname = {"Tom", "Bob", "Uriel", "Sam", "Yann"};

MenuScene::MenuScene (sf::RenderWindow* window) {
    this->window = window;
    isopen = true;

    c->loadFromFile("res/button.png");
    c->setSmooth(true);
}

MenuScene::~MenuScene () {

}

void MenuScene::init () {
    Menu start(640, 300, "start");

    listMenu.push_back(start);

    Menu addplayer(640, 400, "addplayer");

    listMenu.push_back(addplayer);

    Menu deleteplayer(640, 500, "deleteplayer");

    listMenu.push_back(deleteplayer);

    Menu addbot(640, 600, "addbot");

    listMenu.push_back(addbot);
}

std::string MenuScene::getNameMenu (sf::Vector2i pos) {
    for(auto m : listMenu){
        if(abs(pos.x - m.getPostion().x) < 100 && abs(pos.y - m.getPostion().y) < 25){
            return m.getName();
        }
    }

    return "";
}

void MenuScene::addplayer (){
    plist_size++;
}

void MenuScene::deleteplayer (){
    plist_size--;
}

void MenuScene::display () {
    window->clear(sf::Color::White);

    for(auto m : listMenu){
        display_menu(m);
    }

    for (int i = 0; i < plist_size; i++)
    {
        Message m(860, 270 + (60 * i), listname[i]);
        m.addMessage(":");

        Button b(940, 265 + (60 * i), 25, color.colorList[i], c);

        window->draw(m.text);
        window->draw(b.circle);
    }
}

void MenuScene::display_menu (Menu menu) {
    sf::RectangleShape rect = menu.getRectangle();

    window->draw(rect);

    window->draw(menu.getMessage()->text);
}

}