#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>

#include <SFML/Graphics.hpp>
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


int main(int argc,char* argv[])
{
    srand((unsigned) time(NULL));
    std::shared_ptr<State> state(new State());
    Game game;
    game.setState(state);

    if(argc == 1){
        game.begin(TypeScene::MENU);
    }
    else if(argc == 2){
        if(strcmp(argv[1], "hello") == 0)
            cout << "Bonjour le monde !" << endl;
        if(strcmp(argv[1], "state") == 0){
            cout << "Lancer le test " << get_current_dir_name() << endl;
            system("./testScript.sh");
        }
        if(strcmp(argv[1], "engine") == 0){
            game.setDelay(100);
            game.setPlayer(0, {1,1,1});
            game.begin(TypeScene::GAME);
        }
        if(strcmp(argv[1], "render") == 0)
            game.begin(TypeScene::MENU);
        if(strcmp(argv[1], "random_ai") == 0){
            game.setPlayer(1, {1,0,0});
            game.begin(TypeScene::GAME);
        }
        if(strcmp(argv[1], "heuristic_ai") == 0){
            game.setPlayer(1, {0,1,0});
            game.begin(TypeScene::GAME);
        }
        if(strcmp(argv[1], "deep_ai") == 0){
            game.setPlayer(1, {0,0,1});
            game.begin(TypeScene::GAME);
        }
        if(strcmp(argv[1], "rollback") == 0){
            game.setPlayer(0, {2,2,1});
            game.begin(TypeScene::GAME);
        }
        if(strcmp(argv[1], "thread") == 0){
            cout << "Il n'y a pas de thread" << endl;
        }
        if(strcmp(argv[1], "record") == 0){
            cout << "Il n'y a pas de record" << endl;
        }
        if(strcmp(argv[1], "play") == 0){
            cout << "Il n'y a pas de play" << endl;
        }
        if(strcmp(argv[1], "listen") == 0){

        }
        if(strcmp(argv[1], "network") == 0){

        }
        

    }
    else perror("Invaild argument");

    return 0;
}
