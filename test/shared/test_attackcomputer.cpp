
#include <boost/test/unit_test.hpp>

#include "../../src/shared/engine/AttackComputer.h"

using namespace engine;
using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestAttackComputer) 
{
    //Methods tests
    {
        std::map<std::string,int> map = AttackComputer::attackNvM(15,6);
        map = AttackComputer::attackNvM(3,2);
        map = AttackComputer::attackNvM(3,6);
        double proba = AttackComputer::victoryProba(15,6);
        double probatest = 0.9801;
        BOOST_CHECK_EQUAL(proba,probatest);
        proba = AttackComputer::victoryProba(0,0);
        BOOST_CHECK_EQUAL(proba,-1);
    }
}