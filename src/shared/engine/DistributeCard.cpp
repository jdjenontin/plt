#include "DistributeCard.h"
#include <iostream>

namespace engine {

DistributeCard::DistributeCard(){

}

DistributeCard::~DistributeCard(){
    
}

void DistributeCard::execute(){
    std::vector<std::shared_ptr<state::Card>> cardsList = state->getCardsList();
    static int i = 0;
    if(i<cardsList.size()){
        player->addCard(cardsList[i]);
        i++;
    }
}

}