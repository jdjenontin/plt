#include "AiSimple.h"

namespace ai{

AiSimple::AiSimple() {

}

AiSimple::~AiSimple() {
    
}

AiSimple::AiSimple (state::State* state, state::Player* player){
    this->state = state;
    this->player = player;
}

}