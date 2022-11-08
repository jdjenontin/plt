
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/State.h"

using namespace ::state;
using namespace std;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestCountry)
{
  { // Constructor's and getPlayerList test
    State state(3);
    vector<Player*> pList = state.getListPlayers();
    BOOST_CHECK_EQUAL(pList.size(), 3); 
  }
  { //
    State state(3);
    vector<Player*> pList = state.getListPlayers();
    
    // Player1 total countries
    vector<Country*> p1Countries = pList[1]->getListCountry();
    BOOST_CHECK_EQUAL(p1Countries.size(), 0);
  }
}

/* vim: set sw=2 sts=2 et : */
