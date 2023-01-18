#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>
#include <sstream>
#include <thread>
#include <fstream>
#include <stdio.h>
#include <string.h>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "state.h"
#include "render.h"
#include "engine.h"
#include "ai.h"

using namespace std;
using namespace state;
using namespace sf;
using namespace render;
using namespace engine;
using namespace ai;



int netTest() {
    sf::Http http;
    http.setHost("localhost:8000");
    //http.setPort(8000);

    sf::Http::Request request;
    request.setMethod(sf::Http::Request::Get);
    request.setUri("/");

    sf::Http::Response response = http.sendRequest(request);

    if (response.getStatus() == sf::Http::Response::Ok) {
        std::cout << response.getBody() << std::endl;
    } else {
        std::cout << "Error: " << response.getStatus() << std::endl;
    }

    return 0;
}



int main(int argc,char* argv[])
{
    srand((unsigned) time(NULL));

    netTest();

    // std::shared_ptr<State> state(new State());
    // Game game;

    // if(argc == 1){
    //     game.setState(state);
    //     game.begin();
    // }
    // else if(argc == 2){
    //     if(strcmp(argv[1], "hello") == 0)
    //         cout << "Bonjour le monde !" << endl;
    // }
    // else perror("Invaild argument");

    return 0;
}
