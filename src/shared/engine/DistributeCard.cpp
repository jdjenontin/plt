#include "DistributeCard.h"

namespace engine {

DistributeCard::DistributeCard(){

}

DistributeCard::~DistributeCard(){
    
}

void DistributeCard::execute(){
    std::shared_ptr<state::Card> card;
    card = state->drawACard();
    if(card)
        player->addCard(card);
}

}