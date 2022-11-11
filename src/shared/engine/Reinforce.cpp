#include "Reinforce.h"

namespace engine {

Reinforce::Reinforce() {

}

Reinforce::~Reinforce() {

}

void Reinforce::setm_country (state::Country* m_country){
    this->m_country = m_country;
}

void Reinforce::setn_country (state::Country* n_country){
    this->n_country = n_country;
}

}