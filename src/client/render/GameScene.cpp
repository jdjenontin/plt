#include "GameScene.h"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

namespace render
{

sf::Texture cir;

Message cardm(17, 70, "Card");

Button cardb(20, 20, 25, sf::Color::Magenta, &cir);

GameScene::GameScene (sf::RenderWindow* window) {
    this->window = window;

    posCountry = {{100, 140}, {210, 135}, {204, 208}, {290, 220}, {446, 90}, {367, 227}, 
                {208, 302}, {298, 327}, {225, 416}, {310, 480}, {327, 593}, {400, 567}, 
                {341, 685}, {602, 525}, {695, 489}, {752, 587}, {689, 637}, {704, 748}, 
                {815, 750}, {550, 180}, {530, 274}, {648, 160}, {638, 286}, {750, 249}, 
                {563, 361}, {664, 362}, {784, 453}, {863, 323}, {877, 203}, {940, 149}, 
                {1033, 115}, {1021, 224}, {1035, 301}, {1130, 122}, {1171, 267}, {1000, 372}, 
                {931, 466}, {1028, 476}, {1060, 608}, {1166, 593}, {1202, 711}, {1106, 739}};
}

GameScene::~GameScene () {

}

void GameScene::init(std::vector<state::Player *> &pList)
{
    this->pList = pList;

    cir.loadFromFile("res/button.png");
    cir.setSmooth(true);

    for (unsigned i = 0; i < pList.size(); i++)
    {
        Colors color;

        pList[i]->setColor(color.colorList[i]);

        vector<state::Country *> cList = pList[i]->getListCountry();

        for (unsigned j = 0; j < cList.size(); j++)
        {
            cList[j]->setColor(color.colorList[i]);
        }
    }
}

bool GameScene::existCountry(sf::Vector2i pos)
{
    for (unsigned i = 0; i < posCountry.size(); i++)
    {
        if ((abs(pos.x - posCountry[i][0]) < 30) && (abs(pos.y - posCountry[i][1]) < 30))
            return true;
    }
    return false;
}

state::Country *GameScene::findCountry(sf::Vector2i pos)
{
    for (unsigned i = 0; i < posCountry.size(); i++)
    {
        if ((abs(pos.x - posCountry[i][0]) < 30) && (abs(pos.y - posCountry[i][1]) < 30))
            return listcountry[i];
    }
    return {};
}

state::Country GameScene::const_findCountry(sf::Vector2i pos)
{
    for (unsigned i = 0; i < posCountry.size(); i++)
    {
        if ((abs(pos.x - posCountry[i][0]) < 30) && (abs(pos.y - posCountry[i][1]) < 30))
            return *listcountry[i];
    }
    return {};
}

void GameScene::setListcountry(const std::vector<state::Country *> &listcountry)
{
    this->listcountry = listcountry;
}

const std::vector<state::Country *> &GameScene::getListcountry() const
{
    return listcountry;
}

void GameScene::addMessage(Message *message)
{
    listMessage.push_back(message);
}

void GameScene::addListMessage(std::vector<Message *> message)
{
    for (auto m : message)
    {
        listMessage.push_back(m);
    }
}

bool GameScene::isCardButton (sf::Vector2i pos){
    if(abs(pos.x - 45) < 25 && abs(pos.y - 45) < 25)
        return true;
    else return false;
}

void GameScene::display()
{
    Colors color;

    sf::Texture t;

    t.loadFromFile("res/carte.png");
    sf::Sprite background(t);

    // initialiser l'ecran
    window->clear(sf::Color::Cyan);
    window->draw(background);

    // dessiner le bouton de la carte
    window->draw(cardb.circle);
    window->draw(cardm.text);

    // afficher des messages 
    for (auto m : listMessage)
    {
        window->draw(m->text);
    }
    // affichage
    for (unsigned j = 0; j < pList.size(); j++)
    {
        // afficher la liste de joueur
        std::string name = pList[j]->getName();

        Message m(50, 480 + (60 * j), name);
        m.addMessage(":");

        if(pList[j]->getListCountry().size() == 0)
            m.setColor(sf::Color::Red);

        Button b(130, 475 + (60 * j), 25, color.colorList[j], &cir);

        window->draw(m.text);
        window->draw(b.circle);

        // afficher des bouton de pays et aussi le nombre de troup
        vector<state::Country *> cList = pList[j]->getListCountry();

        for (unsigned i = 0; i < cList.size(); i++)
        {
            int num = cList[i]->getId();

            cList[i]->setColor(color.colorList[j]);

            Message m(posCountry[num][0] - 5, posCountry[num][1] - 11, to_string(cList[i]->getNumberOfTroop()), sf::Color::White);

            Button b(posCountry[num][0] - 20, posCountry[num][1] - 20, 25, color.colorList[j], &cir);

            window->draw(b.circle);
            window->draw(m.text);
        }
    }
}

}