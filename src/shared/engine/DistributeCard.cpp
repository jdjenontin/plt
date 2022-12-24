#include "DistributeCard.h"


namespace engine {

DistributeCard::DistributeCard(){

}

DistributeCard::~DistributeCard(){
    
}

void DistributeCard::execute(){
    std::vector<std::shared_ptr<state::Card>> cardsList = state->getCardsList();
    if(cardsList.size()!=0){
        player->addCard(cardsList.back());
        cardsList.pop_back();
    }
    
}

}