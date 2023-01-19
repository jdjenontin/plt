#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>

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
    http.setHost("http://localhost", 8000);

    sf::Http::Request request;
    request.setMethod(sf::Http::Request::Post);
    request.setUri("/");
    request.setHttpVersion(1, 1);
    //request.setField("Content-Type", "application/json");
    request.setBody("{\"name\":\"John\",\"age\":30,\"city\":\"New York\"}");

    sf::Http::Response response = http.sendRequest(request);
    if (response.getStatus() == sf::Http::Response::Ok) {
        std::cout << "Response body: " << response.getBody() << std::endl;
    }
    else {
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
