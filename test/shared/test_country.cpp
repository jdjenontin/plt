
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
    BOOST_CHECK_EQUAL(country.getNumberTroop(),0);
    country.setNumberTroop(5);
    BOOST_CHECK_EQUAL(country.getNumberTroop(),5);
    BOOST_CHECK_EQUAL(country.getColor().toInteger(), 255);
    sf::Color rouge = sf::Color::Red;
    arg.setColor(rouge);
    sf::Color couleur = arg.getColor();
    BOOST_CHECK_EQUAL(couleur.toInteger(), rouge.toInteger());
    
  }

  //Test other methods 
  {
    country.addNumberTroop(2);
    BOOST_CHECK_EQUAL(country.getNumberTroop(), 7);
    country.reduceNumberTroop(4);
    BOOST_CHECK_EQUAL(country.getNumberTroop(), 3);
    BOOST_CHECK_EQUAL(country.getNameCountry(), "");
    BOOST_CHECK_EQUAL(arg.getNameCountry(), "Argentine");
    BOOST_CHECK_EQUAL(arg.getNumberCountry(), 12);
    BOOST_CHECK(arg.isAdjacent(10));
    BOOST_CHECK(!arg.isAdjacent(9));
  }

  



}

/* vim: set sw=2 sts=2 et : */
