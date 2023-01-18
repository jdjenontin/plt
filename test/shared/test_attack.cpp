
#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine/Attack.h"
#include "../../src/shared/state/Country.h"
#include "../../src/shared/state/State.h"

using namespace engine;
using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestAttack) //Fait aussi test_command
{
  std::shared_ptr<state::State> etat(new State());
  etat->init();
  std::shared_ptr<state::Player> joueurAtk = etat->getPlayersList().at(0);
  std::shared_ptr<state::Player> joueurDef = etat->getPlayersList().at(1);
  std::shared_ptr<Attack> attaque(new Attack());
  std::shared_ptr<state::Country> PaysAttaquant(new Country("Argentine", 12));
  std::shared_ptr<state::Country> PaysDefenseur(new Country("Bresil", 11));
  std::shared_ptr<state::Country> PaysTropLoin(new Country("Venezuela", 9));
  etat->getPlayersList().at(0)->addCountry(PaysAttaquant);
  etat->getPlayersList().at(1)->addCountry(PaysDefenseur);
  etat->getPlayersList().at(1)->addCountry(PaysTropLoin);
  PaysAttaquant->setNumberOfTroop(16);
  PaysDefenseur->setNumberOfTroop(6);
  PaysAttaquant->setOwnerId(0);
  PaysDefenseur->setOwnerId(1);
  //Methods tests
  {
    attaque->setPlayer(joueurAtk);
    attaque->setState(etat);
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
    BOOST_CHECK(attaque->isAdjacent());
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