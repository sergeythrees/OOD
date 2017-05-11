#include "stdafx.h"
#include "../GumBallMachineWithState.h"
#include "GumballMachineTestTemplate.h"
#include <boost/mpl/list.hpp>

using namespace std;

typedef boost::mpl::list<int, long, unsigned char> test_types;

	BOOST_TEST_CASE_TEMPLATE_FUNCTION(my_test2, GumballMachineType)
	{
		GumballMachineType f = 0;
		BOOST_TEST(f == 4U);
	}

template <typename GumballMachineType>
void TestGumballMachine(GumballMachineType &machine)
{
	BOOST_CHECK(machine.ToString() == "");	
}

BOOST_AUTO_TEST_CASE(has_coins)
{
	with_state::CGumballMachine machine(5);
	TestGumballMachine(machine);
}
BOOST_AUTO_TEST_SUITE(sdfasd_sdf)
BOOST_TEST_CASE_TEMPLATE_FUNCTION()
BOOST_AUTO_TEST_SUITE_END()