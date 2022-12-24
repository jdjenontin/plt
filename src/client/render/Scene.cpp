#include "Scene.h"

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

namespace render
{

Scene::Scene () {

}


Scene::~Scene()
{
}

bool Scene::isOpen () {
    return isopen;
}

void Scene::open () {
    isopen = true;
}

void Scene::close () {
    isopen = false;
}

void Scene::setWindow(sf::RenderWindow* window) {
    this->window = window;
}

}