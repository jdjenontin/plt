
#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine/UseCard.h"

using namespace engine;
using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestUseCard)
{
  UseCard u = UseCard();
  std::shared_ptr<Player> joueur(new Player());
  std::shared_ptr<Card> cala(new Card("Alaska", Artillery));
  std::shared_ptr<Card> cterr(new Card("Territoires du Nord-Ouest", Cavalry));
  std::shared_ptr<Card> calb(new Card("Alberta", Infantry));
  //Methods tests
  {
    u.setPlayer(joueur);
    joueur->addCard(cala);
    joueur->addCard(cterr);
    joueur->addCard(calb);
    BOOST_CHECK(u.canUseCard());
    u.execute();
    BOOST_CHECK_EQUAL(u.getM_bonusTroop(),10);
    joueur->addCard(cala);
    joueur->addCard(cala);
    joueur->addCard(cala);
    u.execute();
    BOOST_CHECK_EQUAL(u.getM_bonusTroop(),8);
    joueur->addCard(cterr);
    joueur->addCard(cterr);
    joueur->addCard(cterr);
    u.execute();
    BOOST_CHECK_EQUAL(u.getM_bonusTroop(),6);
    joueur->addCard(calb);
    joueur->addCard(calb);
    joueur->addCard(calb);
    u.execute();
    BOOST_CHECK_EQUAL(u.getM_bonusTroop(),4);
    BOOST_CHECK(!(u.canUseCard()));
  }
}