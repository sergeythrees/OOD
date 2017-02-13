#include "stdafx.h"
#include "../WeatherStation/WeatherData.h"
#include "../WeatherStation/Observer.h"

using namespace std;
using namespace boost;


BOOST_AUTO_TEST_SUITE(Observervable_class)

	
	BOOST_AUTO_TEST_CASE(should_notify_obsrvers_in_order_of_their_priority)
	{
		BOOST_CHECK(true);
	}
	


BOOST_AUTO_TEST_SUITE_END()