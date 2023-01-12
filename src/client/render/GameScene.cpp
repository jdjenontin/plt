#include "GameScene.h"

#include <iostream>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

using namespace std;

namespace render
{

sf::Texture cir;
sf::RectangleShape rec1, rec2, rec3;
Message cardm(17, 70, "Card");

Button cardb(20, 20, 25, sf::Color::Magenta, &cir);

GameScene::GameScene () {
    // TO-DO Improve this 
    posCountry = {{124, 170}, {274, 169}, {251, 253}, {355, 272}, {550, 110}, {454, 276}, 
                {252, 370}, {370, 398}, {266, 505}, {375, 594}, {365, 724}, {489, 691}, 
                {406, 866}, {743, 649}, {848, 606}, {936, 729}, {850, 780}, {864, 918}, 
                {1004, 926}, {678, 225}, {643, 342}, {810, 209}, {792, 357}, {936, 294}, 
                {693, 467}, {810, 459}, {971, 564}, {1058, 397}, {1084, 255}, {1165, 177}, 
                {1278, 144}, {1266, 270}, {1279, 370}, {1391, 150}, {1441, 381}, {1225, 463}, 
                {1142, 555}, {1274, 603}, {1295, 775}, {1428, 727}, {1490, 898}, {1362, 913}};
}

GameScene::~GameScene () {

}

void GameScene::initMenu(){
    static sf::Texture t1, t2;
    t1.loadFromFile("res/phase.png");
    t2.loadFromFile("res/end.png");
    sf::Vector2f size1(500, 1080), size2(370, 80);
    rec1.setSize(size1);
    rec1.setPosition(1550, 0);
    rec1.setFillColor(sf::Color::Magenta);

    rec2.setSize(size2);
    rec2.setPosition(1550, 920);
    rec2.setTexture(&t1);
    rec3.setSize(size2);
    rec3.setPosition(1550, 1000);
    rec3.setTexture(&t2);
}

void GameScene::init (std::vector<std::shared_ptr<state::Player>>& pList)
{
    this->pList = pList;

    cir.loadFromFile("res/button.png");
    cir.setSmooth(true);

    for (unsigned i = 0; i < pList.size(); i++)
    {
        Colors color;

        //pList[i]->setColor(color.colorList[i]);

        std::vector<std::shared_ptr<state::Country>> cList = pList[i]->getCountriesList();

        for (unsigned j = 0; j < cList.size(); j++)
        {
            //cList[j]->setColor(color.colorList[i]);
        }
    }
    initMenu();
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

std::shared_ptr<state::Country> GameScene::findCountry(sf::Vector2i pos)
{
    for (unsigned i = 0; i < posCountry.size(); i++)
    {
        if ((abs(pos.x - posCountry[i][0]) < 30) && (abs(pos.y - posCountry[i][1]) < 30))
            return countriesList[i];
    }
    return {};
}

state::Country GameScene::const_findCountry(sf::Vector2i pos)
{
    state::Country c(" ",0);

    for (unsigned i = 0; i < posCountry.size(); i++)
    {
        if ((abs(pos.x - posCountry[i][0]) < 30) && (abs(pos.y - posCountry[i][1]) < 30))
            return *countriesList[i];
    }
    return c;
}

void GameScene::setCountriesList(const std::vector<std::shared_ptr<state::Country>>& countriesList)
{
    this->countriesList = countriesList;
}

const std::vector<std::shared_ptr<state::Country>>& GameScene::getCountriesList() const
{
    return countriesList;
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

void GameScene::displayMenu(){
    window->draw(rec1);
    window->draw(rec2);
    window->draw(rec3);

    // afficher des messages 
    for (auto m : listMessage)
    {
        window->draw(m->text);
    }
}

void GameScene::display()
{
    Colors color;

    sf::Texture t1, t2;
    t1.loadFromFile("res/carte.png");
    sf::Sprite carte(t1), background(t2);

    // initialiser l'ecran
    window->clear(sf::Color::Cyan);
    window->draw(carte);

    // dessiner le bouton de la carte
    window->draw(cardb.circle);
    window->draw(cardm.text);
    displayMenu();

    // affichage
    for (unsigned j = 0; j < pList.size(); j++)
    {
        // afficher la liste de joueur
        std::string name = pList[j]->getName();

        Message m(1600, 210 + (60 * j), name);
        m.addMessage(":");

        if(pList[j]->getCountriesList().size() == 0)
           m.setColor(sf::Color::Red);

        Button b(1680, 205 + (60 * j), 25, color.colorList[j], &cir);

        window->draw(m.text);
        window->draw(b.circle);

        // afficher des bouton de pays et aussi le nombre de troup
        std::vector<std::shared_ptr<state::Country>> cList = pList[j]->getCountriesList();

        for (unsigned i = 0; i < cList.size(); i++)
        {
            int num = cList[i]->getId();

            //cList[i]->setColor(color.colorList[j]);

            Message m(posCountry[num][0] - 5, posCountry[num][1] - 11, to_string(cList[i]->getNumberOfTroop()), sf::Color::White);

            Button b(posCountry[num][0] - 20, posCountry[num][1] - 20, 25, color.colorList[j], &cir);

            window->draw(b.circle);
            window->draw(m.text);
        }
    }
}

}