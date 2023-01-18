
#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine/DistributeCard.h"

using namespace engine;
using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestDistributeCard)
{
    DistributeCard d = DistributeCard();
    std::shared_ptr<State> etat(new State());
    std::shared_ptr<Player> joueur(new Player());
    //Methods tests
    {
        etat->init();
        d.setState(etat);
        d.setPlayer(joueur);
        d.execute();
    }
}