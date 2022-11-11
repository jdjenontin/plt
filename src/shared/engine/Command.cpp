#include "Command.h"

namespace engine {

Command::Command() {

}

Command::~Command() {

}

void Command::setPlayer (state::Player* m_player){
    player = m_player;
}

void Command::setState (state::State* m_state){
    state = m_state;
}

}