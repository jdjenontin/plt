
#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine/Place.h"

using namespace engine;
using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestPlace)
{
  Place p = Place();
  std::shared_ptr<Player> joueur(new Player());
  std::shared_ptr<Country> ala(new Country("Alaska", 0));
  std::shared_ptr<Country> terr(new Country("Territoires du Nord-Ouest", 1));
  std::shared_ptr<Country> alb(new Country("Alberta", 2));
  //Methods tests
  {
    p.bonus_troop = 10;
    p.setPlayer(joueur);
    joueur->addCountry(ala);
    joueur->addCountry(terr);
    joueur->addCountry(alb);
    p.setCountry(ala);
    p.execute();
    p.execute();
    p.execute();
    BOOST_CHECK_EQUAL(p.bonus_troop, 7);
    p.setCountry(terr);
    p.execute();
    p.execute();
    BOOST_CHECK_EQUAL(p.bonus_troop, 5);
    p.setCountry(alb);
    p.execute();
    p.execute();
    p.execute();
    p.execute();
    p.execute();
    BOOST_CHECK_EQUAL(p.bonus_troop, 0);
    BOOST_CHECK_EQUAL(ala->getNumberOfTroop(), 3);
    BOOST_CHECK_EQUAL(terr->getNumberOfTroop(), 2);
    BOOST_CHECK_EQUAL(alb->getNumberOfTroop(), 5);
  }
}