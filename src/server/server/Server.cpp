#include "Server.h"
#include <iostream>
#include <json/json.h>
#include <microhttpd.h>
#include <string.h>
#include "ai/HardAi.h"

using namespace state;
using namespace std;

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

namespace server {

    Json::Value playerPresence(shared_ptr<Player> player){
        vector<int> pres = player->presenceOnContinents();
        Json::Value presJson;

        presJson["GLOBAL"] = player->getCountriesList().size();

        for(unsigned int i = 0; i<pres.size(); i++)
        {
            if((state::Continent) i == state::AFRIQUE){
                presJson["AFRIQUE"] = pres[i];
            }
            else if (i == state::AMERIQUE_SUD)
            {
                presJson["AMERIQUE_SUD"] = pres[i];
            }
            else if (i == state::AMERIQUE_NORD)
            {
                presJson["AMERIQUE_NORD"] = pres[i];
            }
            else if (i == state::EUROPE)
            {
                presJson["EUROPE"] = pres[i];
            }
            else if (i == state::ASIE)
            {
                presJson["ASIE"] = pres[i];
            }
            else if (i == state::OCEANIE)
            {
                presJson["OCEANIE"] = pres[i];
            }
            
        }

        return presJson;
    }

    Server::Server() : listener("http://localhost:8080/") {
        //std::shared_ptr<State> gameState(new State());
        listener.support(methods::GET, std::bind(&Server::handleGET, this, std::placeholders::_1));
        listener.support(methods::POST, std::bind(&Server::handlePOST, this, std::placeholders::_1));
    }
        

    Server::~Server()
    {

    }

    Server::Server(shared_ptr<State> a_gameState) : Server(){
        gameState = a_gameState;
    }

    void Server::handleGET(http_request request)
    {
        auto path = request.relative_uri().path();
        if (path == U("/")) {
            std::ifstream file("res/html_pages/init.html");
            std::string html((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());

            request.reply(status_codes::OK, html, U("text/html"));
        }
        else if (path == U("/state")) {
            string response = DataOps::jsonToString(gameState->serialize());    
            
            request.reply(status_codes::OK, response, U("application/json"));
        }
        else if (path == U("/botbattle")){
            this->bot_battle();
            std::ostringstream oss;
            //oss << "sometext" << somevar << "sometext" << somevar;
            Json::Value occupation;
            for(int i=0; i< gameState->nbOfPlayer; i++)
            {
                std::ostringstream oss;
                oss << "Bot_" << i;
                occupation[oss.str()] = playerPresence(gameState->getPlayersList()[i]);
                if(occupation[oss.str()]["GLOBAL"].asInt() == 42)
                {
                    string html = "<h1> "+ oss.str() + " WIN </h1>";

                    request.reply(status_codes::OK, html, U("text/html"));
                }
            }

            // Réponse bataille en cours
            std::string response = DataOps::jsonToString(occupation);
            request.reply(status_codes::OK, response, U("application/json"));

        }
        else if (path == U("/turn")) {
            request.reply(status_codes::OK, "Hello World!");
        } else if (path == U("/goodbye")) {
            request.reply(status_codes::OK, "Goodbye World!");
        } else {
            request.reply(status_codes::NotFound);
        }
    }

    void Server::handlePOST(http_request request)
    {
        auto path = request.relative_uri().path();
        if (path == U("/")) {
            std::ifstream file("res/html_pages/init.html");
            std::string html((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());

            request.reply(status_codes::OK, html, U("text/html"));
        }
        else if (path == U("/init")) {
            auto body = request.extract_string().get();
            std::cout << body.back() << std::endl;
            gameState->nbOfPlayer = atoi(&body.back());
            // for(int i = 0; i < atoi(&body.back()); i++)
            //     gameState->addPlayer();

            std::cout<< "Here 1" << std::endl;
            gameState->init();
            std::cout<< "Here 2" << std::endl;
            string response = DataOps::jsonToString(gameState->serialize());
            
            request.reply(status_codes::OK, response, U("application/json"));
        }
        else if (path == U("/attack")) {
            request.reply(status_codes::OK, "Attack");
        }
        else if (path == U("/place")) {
            request.reply(status_codes::OK, "Place");
        } 
        else if (path == U("/reinforce")) {
            request.reply(status_codes::OK, "Reinforce");
        } 
        else {
            request.reply(status_codes::NotFound);
        }
    }

    int Server::bot_battle()
    {
        static int i = 0;
        int nPlayer = gameState->nbOfPlayer;
        ai::HardAi bot;
        bot.setState(gameState);
        bot.execute(gameState->getPlayersList()[i%nPlayer]);
        i++;
        return 0;
    }

    int Server::run()
    {
        listener
            .open()
            .then([&]() { printf("Starting to listen\n"); })
            .wait();
        return 0;
    }
}