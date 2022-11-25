#include "UseCard.h"
#include <iostream>
#include <algorithm>
#include <iterator>

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

    

    

    
    if ((m_number_artillery > 0 && m_number_cavalry > 0 && m_number_infantry > 0) || m_number_artillery >=3 || m_number_cavalry >=3 || m_number_infantry>=3)
        return true;

    return false;
}

int UseCard::getM_bonusTroop() const{
    return m_bonusTroop;
}

/**
 * @brief Compute the number of bonus troop and delete the cards from the player cards
*/
void UseCard::execute(){
    std::vector<state::Card *> list_card = player->getListCard();
    std::vector<state::Card *>::iterator it_artillery = std::find_if(list_card.begin(), list_card.end(), cardType(state::Artillery));
    std::vector<state::Card *>::iterator it_cavalry = std::find_if(list_card.begin(), list_card.end(), cardType(state::Cavalry));
    std::vector<state::Card *>::iterator it_infantry = std::find_if(list_card.begin(), list_card.end(), cardType(state::Infantry));
    bool can_use = this->canUseCard();
    if(can_use){
        if ((m_number_artillery > 0 && m_number_cavalry > 0 && m_number_infantry > 0)){
            m_bonusTroop = 10;
            
            player->deleteCard(*it_artillery);
            player->deleteCard(*it_cavalry);
            player->deleteCard(*it_infantry);
        }
        else if(m_number_artillery >= 3){
            m_bonusTroop = 8;
            for (int i = 0; i<3; i++)
                player->deleteCard(*(it_artillery+i));
        }
        else if (m_number_cavalry >= 3)
        {
            m_bonusTroop = 6;
            for (int i = 0; i<3; i++)
                player->deleteCard(*(it_cavalry+i));
        }
        else if (m_number_infantry >= 3)
        {
            m_bonusTroop = 4;
            for (int i = 0; i<3; i++)
                player->deleteCard(*(it_infantry+i));
        }
        
    }
}

}