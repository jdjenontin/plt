
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/State.h"

using namespace ::state;
using namespace std;


/**
 * @brief Predicate to test if every troopNumber value is less than a sepecific one
 * @param lCountry : List of pointers on countries
 * @param troopMin : minimal troop number
*/
boost::test_tools::predicate_result validate_country_troop(vector<std::shared_ptr<Country>> lCountry, int troopMin)
{

  for (auto country : lCountry) {
    if (country->getNumberOfTroop() < troopMin) return false;
  }
  return true;

}

BOOST_AUTO_TEST_CASE(TestState)
{
  {
    std::shared_ptr<State> state(new State());
    state->init();
    state->IncrementTurn();
    //state->buildCards();
    BOOST_CHECK_EQUAL(state->getTurn(),1);
    vector<std::shared_ptr<Player>> pList = state->getPlayersList();
    vector<std::shared_ptr<Card>> CardsList = state->getCardsList();
    vector<std::shared_ptr<Country>> CountryList = state->getCountriesList();
    int PlayerOrder = state->getOrderPlayer();
    BOOST_CHECK_EQUAL(pList.size(), state->nbOfPlayer); 
    BOOST_CHECK_EQUAL(CardsList.size(), 42); 
    BOOST_CHECK_EQUAL(CountryList.size(), 42); 

    BOOST_CHECK_EQUAL(PlayerOrder, 0);
    state->ChangePlaying();
    PlayerOrder = state->getOrderPlayer();
    BOOST_CHECK_EQUAL(PlayerOrder, 1);
    state->ChangePlaying();
    PlayerOrder = state->getOrderPlayer();
    BOOST_CHECK_EQUAL(PlayerOrder, 0);

    vector<std::shared_ptr<Country>> Player2Countries = pList[1]->getCountriesList();
    int size = Player2Countries.size();
    std::cout << size << std::endl;
    for (int i = 0; i<size; i++) {
      state->getPlayersList().at(1)->deleteCountry(Player2Countries.at(i));
    }
    std::cout << state->getPlayersList().at(1)->getCountriesList().size() << std::endl;
    state->ChangePlaying();
    PlayerOrder = state->getOrderPlayer();
    BOOST_CHECK_EQUAL(PlayerOrder, 0);
  }
}

/* vim: set sw=2 sts=2 et : */
