
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Calculation.h"
#include "../../src/shared/state/Player.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestCalculation)
{
    Calculation calculation;
    std::shared_ptr<Country> arg(new Country("Argentine", 12));
    std::shared_ptr<Country> bre(new Country ("Bresil", 11));
    std::vector<std::shared_ptr<Country>> listePays;
    listePays.push_back(arg);
    listePays.push_back(bre);


    // Tests getters setters
    {
      std::shared_ptr<Player> joueur(new Player());
      joueur->addCountry(arg);
      joueur->addCountry(bre);
      BOOST_CHECK_EQUAL(calculation.areConnected(joueur, arg, bre), true);
      BOOST_CHECK_EQUAL(calculation.isCountryInList(bre, listePays), true);
      std::vector<int> tab = calculation.shuffledTab(2);
    }
}