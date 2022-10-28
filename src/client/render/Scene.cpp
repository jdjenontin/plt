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

Scene::Scene (sf::RenderWindow &window){
    
}

bool Scene::existCountry (sf::Vector2i pos){
    for(unsigned i = 0; i < posCountry.size(); i++){
        if((abs(pos.x - posCountry[i][0]) < 30 ) && (abs(pos.y - posCountry[i][1]) < 30 ))
            return true;
    }
    return false;
}

state::Country Scene::findCountry (sf::Vector2i pos){
    for(unsigned i = 0; i < posCountry.size(); i++){
        if((abs(pos.x - posCountry[i][0]) < 30 ) && (abs(pos.y - posCountry[i][1]) < 30 ))
            return listcountry[i];
    }
    return {};
}

void Scene::setListCountry(const std::vector<state::Country> v_listcountry){
    listcountry = v_listcountry;
}

void Scene::addMessage (Message* message){
    listMessage.push_back(message);
}

void Scene::display_message (){
    for(auto m : listMessage){
        std::string str = m->text.getString();
        std::cout << str << std::endl;
        window.draw(m->text);
    }
}

    
}