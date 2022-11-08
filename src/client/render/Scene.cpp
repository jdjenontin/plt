#include "Scene.h"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

namespace render{

Scene::Scene(){
    posCountry = {  {100,140},{210,135},{204,208},{290,220},{446,90},{367,227},
                    {208,302},{298,327},{225,416},{310,480},{327,593},{400,567},
                    {341,685},{602,525},{695,489},{752,587},{689,637},{704,748},
                    {815,750},{550,180},{530,274},{648,160},{638,286},{750,249},
                    {563,361},{664,362},{784,453},{863,323},{877,203},{940,149},
                    {1033,115},{1021,224},{1035,301},{1130,122},{1171,267},{1000,372},
                    {931,466},{1028,476},{1060,608},{1166,593},{1202,711},{1106,739},};
}

Scene::~Scene(){

}

Scene::Scene (sf::RenderWindow* window){
    this->window = window;

    posCountry = {  {100,140},{210,135},{204,208},{290,220},{446,90},{367,227},
                    {208,302},{298,327},{225,416},{310,480},{327,593},{400,567},
                    {341,685},{602,525},{695,489},{752,587},{689,637},{704,748},
                    {815,750},{550,180},{530,274},{648,160},{638,286},{750,249},
                    {563,361},{664,362},{784,453},{863,323},{877,203},{940,149},
                    {1033,115},{1021,224},{1035,301},{1130,122},{1171,267},{1000,372},
                    {931,466},{1028,476},{1060,608},{1166,593},{1202,711},{1106,739}};
}

void Scene::init(std::vector<state::Player*>& pList, sf::Texture* texture){
    this->pList = pList;

    for(unsigned i = 0; i < pList.size(); i++){
        Colors color;

        Message m(50, 480 + (60 * i), "Player");
        m.setintMessage(i+1);
        m.addMessage(":");

        Button b(150, 475 + (60 * i), 25, color.colorList[i], texture);

        pList[i]->setColor(color.colorList[i]);

        const_listButton.push_back(b);

        const_listMessage.push_back(m);

        vector<state::Country*> cList = pList[i]->getListCountry();

        for(unsigned j = 0; j < cList.size(); j++){
            cList[j]->setColor(color.colorList[i]);
        }
    }
}

bool Scene::existCountry (sf::Vector2i pos){
    for(unsigned i = 0; i < posCountry.size(); i++){
        if((abs(pos.x - posCountry[i][0]) < 30 ) && (abs(pos.y - posCountry[i][1]) < 30 ))
            return true;
    }
    return false;
}

state::Country* Scene::findCountry (sf::Vector2i pos){
    for(unsigned i = 0; i < posCountry.size(); i++){
        if((abs(pos.x - posCountry[i][0]) < 30 ) && (abs(pos.y - posCountry[i][1]) < 30 ))
            return listcountry[i];
    }
    return {};
}

state::Country Scene::const_findCountry (sf::Vector2i pos){
    for(unsigned i = 0; i < posCountry.size(); i++){
        if((abs(pos.x - posCountry[i][0]) < 30 ) && (abs(pos.y - posCountry[i][1]) < 30 ))
            return *listcountry[i];
    }
    return {};
}

void Scene::setListcountry(const std::vector<state::Country*> & listcountry){
    this->listcountry = listcountry;
}

const std::vector<state::Country*> & Scene::getListcountry() const{
    return listcountry;
}

void Scene::addMessage (Message* message){
    listMessage.push_back(message);
}

void Scene::addListMessage (std::vector<Message*> message){
    for(auto m : message){
        listMessage.push_back(m);
    }
}

void Scene::display_message (){
    sf::Texture t;

    t.loadFromFile("res/carte.png");
    sf::Sprite background(t);

    window->clear(sf::Color::White);	
    window->draw(background);

    for(auto m : listMessage){
        window->draw(m->text);
    }

    for(auto m : const_listMessage){
        window->draw(m.text);
    }

    for(auto b : const_listButton){
        window->draw(b.circle);
    }

    Colors color;

    sf::Texture circle;    
    
    circle.loadFromFile("res/button.png");
    circle.setSmooth(true);

    for(unsigned j = 0; j < pList.size(); j++){
        vector<state::Country*> cList = pList[j]->getListCountry();

        for(unsigned i = 0; i < cList.size(); i++){
            int num = cList[i]->getNumberCountry();

            cList[i]->setColor(color.colorList[j]);

            Message m(posCountry[num][0] - 5, posCountry[num][1] - 11, to_string(cList[i]->getNumberTroop()));

            Button b(posCountry[num][0] - 20, posCountry[num][1] - 20, 25, color.colorList[j], &circle);

            window->draw(b.circle);
            window->draw(m.text);
        }
    }
}

    
}