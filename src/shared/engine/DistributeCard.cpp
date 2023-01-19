#include "DistributeCard.h"

namespace engine {

DistributeCard::DistributeCard(){

}

DistributeCard::~DistributeCard(){
    
}

void DistributeCard::execute(){
    std::shared_ptr<state::Card> card;
    card = state->drawACard();
    player->addCard(card);
}

}