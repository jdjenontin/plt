#include "DistributeCard.h"
//#include "Dice.h"
namespace engine {

DistributeCard::DistributeCard(){

}

DistributeCard::~DistributeCard(){
    
}

void DistributeCard::execute(){
    static std::vector<state::Card *> list_card = state->getListCard();
    if(list_card.size()!=0){
        player->addCard(list_card.back());
        list_card.pop_back();
    }
    
}

}