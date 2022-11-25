#include "UseCard.h"
#include <iostream>
#include <algorithm>

/**
 * Predicat
*/
class cardType{
    private:
        state::TypeCard m_type;
    
    public:
        cardType(state::TypeCard type){
            m_type = type;
        }

        bool operator()(state::Card* card) const{
            return m_type == card->typeCard;
        }
};


namespace engine {

/**
 * Constructor 
*/
UseCard::UseCard(){

}
/**
 * Destructor
*/
UseCard::~UseCard(){
    
}
/**
 * @brief Check if the player have 3 different type or the same type of card 3 times
 * @return true if yes
*/
bool UseCard::canUseCard(){
    std::vector<state::Card *> list_card = player->getListCard();
    m_number_artillery = std::count_if(list_card.begin(), list_card.end(), cardType(state::Artillery));
    m_number_cavalry = std::count_if(list_card.begin(), list_card.end(), cardType(state::Cavalry));
    m_number_infantry = std::count_if(list_card.begin(), list_card.end(), cardType(state::Infantry));

    
    if ((m_number_artillery > 0 && m_number_cavalry > 0 && m_number_infantry > 0) || m_number_artillery >3 || m_number_cavalry >3 || m_number_infantry>3)
        return true;
    /*
    for(auto card : list_card){
        if(card->typeCard == state::Artillery)
        {
            m_usedCard.insert({1, card});
            artillery++;
        }        
        else if (card->typeCard == state::Cavalry)
        {
            m_usedCard.insert({2, card});
            cavalry++;
        }
        else
        {
            m_usedCard.insert({3, card});
            infantry++;
        }

        if(artillery > 0 && cavalry > 0 && infantry > 0){
            return true;
        }
    }*/

    return false;
}

/**
 * @brief Compute the number of bonus troop and delete the cards from the player cards
*/
void UseCard::execute(){
    bool can_use = this->canUseCard();
    if(can_use){
        if ((m_number_artillery > 0 && m_number_cavalry > 0 && m_number_infantry > 0)){
            m_bonusTroop = 10;
        }
        else if(m_number_artillery > 3){
            m_bonusTroop = 8;
        }
        else if (m_number_cavalry)
        {
            m_bonusTroop = 6;
        }
        else if (m_number_infantry)
        {
            m_bonusTroop = 4;
        }
        
    }
}

}