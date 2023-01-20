#include <iostream>
#include "server.h"

#include <vector>
#include <memory>

using namespace std;
using namespace server;
const int PORT = 8000;

int main()
{
    shared_ptr<state::State> gameState(new state::State());
    Server gameServer(gameState);
    gameServer.run();
    std::cout << "API is running. Press enter to exit." << std::endl;
    std::cin.get();
    gameServer.listener.close().wait();

    return 0;
}