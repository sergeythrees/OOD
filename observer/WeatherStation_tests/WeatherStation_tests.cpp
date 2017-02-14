#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "../WeatherStation/Observer.h"

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(Observer_class)

	
	BOOST_AUTO_TEST_CASE(should_know_from_which_observable_object_notification_came)
	{
		class Observer : public IObserver<int>
		{
		public:
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

		ostringstream output;
		Observer observer(output);
		Observable observable1;
		observable1.SetName("1");
		Observable observable2;
		observable2.SetName("2");

		observable1.RegisterObserver(observer, 0);
		observable2.RegisterObserver(observer, 0);
		observable1.NotifyObservers();
		observable2.NotifyObservers();

		BOOST_CHECK(output.str() == "12");
		output = ostringstream();
		observable2.NotifyObservers();
		observable1.NotifyObservers();
		BOOST_CHECK_EQUAL(output.str(), "21");

	}
	


BOOST_AUTO_TEST_SUITE_END()