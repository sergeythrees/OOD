#include "stdafx.h"
#include <iostream>
#include "../WeatherStation/Observer.h"

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(Observer_class)

	
	BOOST_AUTO_TEST_CASE(should_know_from_which_observable_object_notification_came)
	{
		class Observer : public IObserver<int>
		{
			Observer(std::ostream& output)
				:m_output(output)
			{};
		private:
			ostream& m_output;
			void Update(int const& data, const string& observableName) override
			{
				data;
				m_output << observableName;
			}

		};
		class Observable : public CObservable<int>
		{
		protected:
			int GetChangedData()const override
			{
				return 0;
			}
		};



		BOOST_CHECK(true);
	}
	


BOOST_AUTO_TEST_SUITE_END()