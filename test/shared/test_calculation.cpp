
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
    Country arg("Argentine", 12);
    Country bre("Bresil", 11);
    std::vector<Country*> listePays;
    listePays.push_back(&arg);
    listePays.push_back(&bre);


    // Tests getters setters
    {
      calculation.compute(&arg, &bre);
      Player joueur = Player();
      joueur.addCountry(&arg);
      joueur.addCountry(&bre);
      BOOST_CHECK_EQUAL(calculation.areConnected(&joueur, &arg, &bre), true);
      BOOST_CHECK_EQUAL(calculation.isCountryInList(&bre, listePays), true);
      std::vector<int> tab = calculation.shuffledTab(2);
    }
}