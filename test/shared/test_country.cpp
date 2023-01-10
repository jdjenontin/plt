
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Country.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestCountry)
{

  std::shared_ptr<Country> country(new Country());
  std::shared_ptr<Country> blabla(new Country("random", 43, 100, 200));
  std::shared_ptr<Country> ala(new Country("Alaska", 0));
  std::shared_ptr<Country> alb(new Country("Alberta", 2));

  // Test getters setters
  {
    country->setNumberOfTroop(5);
    country->setOwnerId(18);
    BOOST_CHECK_EQUAL(ala->getId(),0);
    BOOST_CHECK_EQUAL(ala->getName(),"Alaska");
    BOOST_CHECK_EQUAL(country->getNumberOfTroop(),5);
    BOOST_CHECK_EQUAL(country->getOwnerId(), 18);
  }

  //Test other methods 
  {
    country->addTroop(2);
    BOOST_CHECK_EQUAL(country->getNumberOfTroop(), 7);
    country->reduceTroop(4);
    BOOST_CHECK_EQUAL(country->getNumberOfTroop(), 3);
    BOOST_CHECK(ala->isAdjacent(1));
    BOOST_CHECK(!ala->isAdjacent(9));
    ala->setNumberOfTroop(50);
    alb->setNumberOfTroop(2);
    BOOST_CHECK(country->troopComparaison(alb,ala));
    BOOST_CHECK(country->idComparaison(ala,alb));
    country->print();
  }

}

/* vim: set sw=2 sts=2 et : */
