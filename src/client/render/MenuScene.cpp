#include "MenuScene.h"

#include <iostream>

namespace render {

MenuScene::MenuScene (sf::RenderWindow* window) {
    this->window = window;
    isopen = true;
}

MenuScene::~MenuScene () {

}

void MenuScene::init () {
    Menu start(640, 300, "start");

    listMenu.push_back(start);

    Menu addplayer(640, 500, "addplayer");

    listMenu.push_back(addplayer);
}

std::string MenuScene::getNameMenu (sf::Vector2i pos) {
    for(auto m : listMenu){
        if(abs(pos.x - m.getPostion().x) < 100 && abs(pos.y - m.getPostion().y) < 25){
            return m.getName();
        }
    }

    return "";
}

void MenuScene::display () {
    window->clear(sf::Color::White);

    for(auto m : listMenu){
        display_menu(m);
    }
}

void MenuScene::display_menu (Menu menu) {
    sf::RectangleShape rect = menu.getRectangle();

    window->draw(rect);

    window->draw(menu.getMessage()->text);
}

}