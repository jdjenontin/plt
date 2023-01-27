
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Dice.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestDice)
{
    Dice dice(1, 1);
    Dice dé = Dice();
    //Methods tests
    {
      BOOST_CHECK_EQUAL(dice.thrown(), 1);
      dice.updateDice(3,1);
      BOOST_CHECK_EQUAL(dice.thrown(), -1);
    }
}