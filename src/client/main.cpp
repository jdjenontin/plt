#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>
#include <fstream>

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
    
    Reinforce reinforce;
    
    Game game;

    game.setState(state);
    game.begin();

    return 0;
}
