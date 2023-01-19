#include "DistributeCard.h"
#include <iostream>

namespace engine {

DistributeCard::DistributeCard(){

}

DistributeCard::~DistributeCard(){
    
}

//TO-DO improve
void DistributeCard::execute(){
    std::vector<std::shared_ptr<state::Card>> cardsList = state->getCardsList();
    static unsigned int i = 0;
    if(i<cardsList.size()){
        player->addCard(cardsList[i]);
        i++;
    }
}

}