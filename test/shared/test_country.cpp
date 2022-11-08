
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state/Country.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestCountry)
{
  {
    Country country;
    country.setNumberTroop(5);
    BOOST_CHECK_EQUAL(country.getNumberTroop(),5);
  }
}

/* vim: set sw=2 sts=2 et : */
