
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Calculation.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestCalculation)
{
    Calculation calculation;
    Country arg("Argentine", 12);
    Country bre("Bresil", 11);
    Country *pArg = &arg;
    Country *pBre = &bre;

    // Tests getters setters
    {
        
    }
}