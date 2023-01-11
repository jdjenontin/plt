#include "CardScene.h"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

namespace render{

sf::Texture* circle = new sf::Texture();

Button gameb(20, 20, 25, sf::Color::Magenta, circle),
       changeb(1050, 20, 25, sf::Color::Blue, circle); 

Message change(960, 30, "change");

CardScene::CardScene(){
    circle->loadFromFile("res/button.png");
    circle->setSmooth(true);
}

CardScene::~CardScene(){

}

void CardScene::init(){
    std::vector<std::shared_ptr<state::Card>> clist = player->getCardsList();
    cardsList = {};

    for(unsigned int i = 0; i < clist.size(); i++){
        if(clist[i]->typeCard == state::TypeCard::Infantry){
            Card card(100 + 230*(i%5), 100 + 300*(i/5), "Infantry", clist[i]->getName());
            cardsList.push_back(card);
        }
        else if(clist[i]->typeCard == state::TypeCard::Cavalry){
            Card card(100 + 230*(i%5), 100 + 300*(i/5), "Cavalry", clist[i]->getName());
            cardsList.push_back(card);
        }
            
        else if(clist[i]->typeCard == state::TypeCard::Artillery){
            Card card(100 + 230*(i%5), 100 + 300*(i/5), "Artillery", clist[i]->getName());
            cardsList.push_back(card);
        }
    }
}

bool CardScene::isGameButton (sf::Vector2i pos){
    if(abs(pos.x - 45) < 25 && abs(pos.y - 45) < 25)
        return true;
    else return false;
}

bool CardScene::isChangeButton (sf::Vector2i pos){
    if(abs(pos.x - 1075) < 25 && abs(pos.y - 45) < 25)
        return true;
    else return false;
}


void CardScene::setPlayer (std::shared_ptr<state::Player>& player){
    this->player = player;
}

void CardScene::display(){
    window->clear(sf::Color::Cyan);

    window->draw(gameb.circle);
    window->draw(changeb.circle);
    window->draw(change.text);
    std::cout << cardsList.size() << std::endl;

    for(auto c : cardsList){
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