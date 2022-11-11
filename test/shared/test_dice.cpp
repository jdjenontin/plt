
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
    //Methods tests
    {
        std::uniform_int_distribution<int> dist{1,1};
        BOOST_CHECK_EQUAL(dice.distrib, dist);
        BOOST_CHECK_EQUAL(dice.thrown(), 1);
    }
}