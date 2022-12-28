#include "Command.h"

namespace engine {

Command::Command() {

}

Command::~Command() {

}

void Command::setPlayer(const std::shared_ptr<state::Player>& player){
    this->player = player;
}

void Command::setState(const std::shared_ptr<state::State>& state){
    this->state = state;
}

}