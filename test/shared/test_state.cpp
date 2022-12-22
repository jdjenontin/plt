
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/State.h"

using namespace ::state;
using namespace std;


/**
 * @brief Predicate to test if every troopNumber value is less than a sepecific one
 * @param lCountry : List of pointers on countries
 * @param troopMin : minimal troop number
*/
boost::test_tools::predicate_result validate_country_troop(vector<Country*> lCountry, int troopMin)
{

  for (auto country : lCountry) {
    if (country->getNumberOfTroop() < troopMin) return false;
  }
  return true;

}

BOOST_AUTO_TEST_CASE(TestState)
{
  { // Constructor's and getPlayerList test
    State state(3);
    vector<Player*> pList = state.getListPlayers();
    BOOST_CHECK_EQUAL(pList.size(), 3); 
  }
  { // Test init()
    State state(3);
    vector<Player*> pList = state.getListPlayers();
    state.init();

    // Second player's countries
    vector<Country*> p1Countries = pList[1]->getCountriesList();

    // Check if the player 2 have 14 countries
    BOOST_CHECK_EQUAL(p1Countries.size(), 14);

    // Check if each country have minimun 2 troops
    BOOST_CHECK(validate_country_troop(pList[1]->getCountriesList(), 2));

    // Check the total troop own by player 2
    int totalTroops(0);

    for (auto country : p1Countries){
      totalTroops += country -> getNumberOfTroop();
    }
    BOOST_CHECK_EQUAL(totalTroops, 35);
    
  }
  {
    State state(5);
    vector<Player*> pList = state.getListPlayers();
    state.init();

    // Player1 total countries
    vector<Country*> p5Countries = pList[4]->getCountriesList();
    BOOST_CHECK_EQUAL(p5Countries.size(), 8);
  } 

  {
    State state(5);
    vector<Country*> lCountries = state.getListCountires();
    vector<Card> lCards = state.getCardsList();
    //BOOST_CHECK_EQUAL(lCountries.size(), 16);
    //BOOST_CHECK_EQUAL(lCards.size(), 16);

  }
  {
    State state(3);
    vector<Player*> pList = state.getListPlayers();
    vector<Country*> lCountries = pList[1]->getCountriesList();
    Country* a_country = lCountries[0];
    a_country->setColor(pList[1]->getColor());

    Player* owner = state.belongsto(a_country);

    BOOST_CHECK_EQUAL(owner, pList[1]);
  }

}

/* vim: set sw=2 sts=2 et : */
