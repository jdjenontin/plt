
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Country.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestCountry)
{

  Country country;
  Country arg("Argentine", 12);


  // Test getters setters
  {
    // BOOST_CHECK_EQUAL(country.getNumberOfTroop(),0);
    // country.setNumberOfTroop(5);
    // BOOST_CHECK_EQUAL(country.getNumberOfTroop(),5);
    // BOOST_CHECK_EQUAL(country.getColor().toInteger(), 255);
    // sf::Color rouge = sf::Color::Red;
    // arg.setColor(rouge);
    // sf::Color couleur = arg.getColor();
    // BOOST_CHECK_EQUAL(couleur.toInteger(), rouge.toInteger());
    
  }

  //Test other methods 
  {
    country.addTroop(2);
    BOOST_CHECK_EQUAL(country.getNumberOfTroop(), 7);
    country.reduceTroop(4);
    BOOST_CHECK_EQUAL(country.getNumberOfTroop(), 3);
    BOOST_CHECK_EQUAL(country.getName(), "");
    BOOST_CHECK_EQUAL(arg.getName(), "Argentine");
    BOOST_CHECK_EQUAL(arg.getId(), 12);
    BOOST_CHECK(arg.isAdjacent(10));
    BOOST_CHECK(!arg.isAdjacent(9));
  }

  



}

/* vim: set sw=2 sts=2 et : */
