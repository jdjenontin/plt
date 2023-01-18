
#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine/Engine.h"

using namespace engine;
using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestEngine)
{
  Engine e = Engine();
  std::shared_ptr<State> etat(new State());
  std::shared_ptr<Player> joueur(new Player());
  std::shared_ptr<Country> ala(new Country("Alaska", 0));
  std::shared_ptr<Country> terr(new Country("Territoires du Nord-Ouest", 1));
  std::shared_ptr<Country> PaysTropLoin(new Country("Venezuela", 9));
  ala->setNumberOfTroop(5);
  terr->setNumberOfTroop(5);
  PaysTropLoin->setNumberOfTroop(5);
  //Methods tests
  {
    e.init(etat);
    e.setPlayer(joueur);
    e.setCountry(ala);
  }
}