
#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine/Reinforce.h"

using namespace engine;
using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestReinforce)
{
  Reinforce r = Reinforce();
  std::shared_ptr<Player> joueur(new Player());
  std::shared_ptr<Country> ala(new Country("Alaska", 0));
  std::shared_ptr<Country> terr(new Country("Territoires du Nord-Ouest", 1));
  std::shared_ptr<Country> PaysTropLoin(new Country("Venezuela", 9));
  //Methods tests
  {
    ala->setNumberOfTroop(5);
    terr->setNumberOfTroop(1);
    PaysTropLoin->setNumberOfTroop(15);
    joueur->addCountry(ala);
    joueur->addCountry(terr);
    joueur->addCountry(PaysTropLoin);
    r.setPlayer(joueur);
    r.setM_country(ala);
    r.setN_country(terr);
    BOOST_CHECK(r.existM_country());
    BOOST_CHECK(r.existN_country());
    BOOST_CHECK_EQUAL(r.getM_country()->getId(),0);
    BOOST_CHECK_EQUAL(r.getN_country()->getId(),1);
    BOOST_CHECK_EQUAL(r.execute(),1);
    r.setM_country(PaysTropLoin);
    BOOST_CHECK_EQUAL(r.execute(),0);
  }
}