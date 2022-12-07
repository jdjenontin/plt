#include "ExecutionAi.h"

namespace ai{

ExecutionAi::ExecutionAi(){

}

ExecutionAi::~ExecutionAi(){

}

void ExecutionAi::init (state::Player* player, state::State* state){
    this->player = player;
    this->state = state;
}

}