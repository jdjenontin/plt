
#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine/Attack.h"
#include "../../src/shared/state/Country.h"

using namespace engine;
using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestAttack) //Fait aussi test_command
{
  std::shared_ptr<Command> commande(new Command());
  std::shared_ptr<state::Player> joueur(new Player(1));
  std::shared_ptr<state::State> etat(new State());
  std::shared_ptr<Attack> attaque(new Attack());
  std::shared_ptr<state::Country> PaysAttaquant(new Country("Argentine", 12));
  std::shared_ptr<state::Country> PaysDefenseur(new Country("Bresil", 11));
  std::shared_ptr<state::Country> PaysTropLoin(new Country("Venezuela", 9));
  PaysAttaquant->setNumberOfTroop(16);
  PaysDefenseur->setNumberOfTroop(6);
  PaysAttaquant->setOwnerId(1);
  PaysDefenseur->setOwnerId(2);
  //Methods tests
  {
    commande->setPlayer(joueur);
    commande->setState(etat);
    attaque->setAttackCountry(PaysAttaquant);
    attaque->setDefCountry(PaysDefenseur);
    attaque->setAttackType(SOLO);
    BOOST_CHECK_EQUAL(attaque->compTroops().at(0), 1);
    BOOST_CHECK_EQUAL(attaque->compTroops().at(1), 1);
    attaque->setAttackType(DOUBLE);
    BOOST_CHECK_EQUAL(attaque->compTroops().at(0), 2);
    BOOST_CHECK_EQUAL(attaque->compTroops().at(1), 2);
    attaque->setAttackType(MULTIPLE);
    BOOST_CHECK_EQUAL(attaque->compTroops().at(0), 15);
    BOOST_CHECK_EQUAL(attaque->compTroops().at(1), 6);
    BOOST_CHECK(attaque->ableToAttack());
    attaque->moveTroop();
    BOOST_CHECK_EQUAL(attaque->getAttackCountry()->getNumberOfTroop(), 15);
    BOOST_CHECK_EQUAL(attaque->getDefCountry()->getNumberOfTroop(), 7);
    BOOST_CHECK_EQUAL(attaque->execute(), 1);
    std::map<std::string,int> sum = attaque->getAttSummary();
    attaque->setAttackCountry(PaysTropLoin);
    BOOST_CHECK_EQUAL(attaque->execute(), 0);
  }
}