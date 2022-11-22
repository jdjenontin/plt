#include "CardScene.h"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

namespace render{

sf::Texture* circle = new sf::Texture();

Button gameb(20, 20, 25, sf::Color::Magenta, circle);

CardScene::CardScene(sf::RenderWindow* window){
    this->window = window;
    
    circle->loadFromFile("res/button.png");
    circle->setSmooth(true);
}

CardScene::~CardScene(){

}

void CardScene::init(){
    std::vector<state::Card*> clist = player->getListCard();

    for(unsigned int i = 0; i < clist.size(); i++){
        if(clist[i]->typeCard == state::TypeCard::Infantry){
            Card card(100 + 250*i, 100, "Infantry", clist[i]->getNameCountry());
            listCard.push_back(card);
        }
        else if(clist[i]->typeCard == state::TypeCard::Cavalry){
            Card card(100 + 250*i, 100, "Cavalry", clist[i]->getNameCountry());
            listCard.push_back(card);
        }
            
        else if(clist[i]->typeCard == state::TypeCard::Artillery){
            Card card(100 + 250*i, 100, "Artillery", clist[i]->getNameCountry());
            listCard.push_back(card);
        }
    }
}

bool CardScene::isGameButton (sf::Vector2i pos){
    if(abs(pos.x - 45) < 25 && abs(pos.y - 45) < 25)
        return true;
    else return false;
}

void CardScene::setPlayer (state::Player* player){
    this->player = player;
}

void CardScene::display(){
    window->clear(sf::Color::Cyan);

    window->draw(gameb.circle);

    for(auto c : listCard){
        display_card(c);
    }
}

void CardScene::display_card (Card card){
    sf::RectangleShape rec = card.getRectangle();

    window->draw(rec);
    window->draw(card.getCountry()->text);
    window->draw(card.getName()->text);

    sf::Sprite pion = card.getPion();

    window->draw(pion); 
}

}