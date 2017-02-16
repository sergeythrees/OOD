#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "../WeatherStationDuo/Observer.h"

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(Observer_class)

	
	BOOST_AUTO_TEST_CASE(should_know_from_which_observable_object_notification_came)
	{
	struct info
	{
		string observableName;
	};
		

		class Observer : public IObserver<info>
		{
		public:
			Observer(std::ostream& output)
				:m_output(output)
			{};
		private:
			ostream& m_output;
			void Update(info const& data, const IObservable<info>& observable) override
			{
				observable;
				m_output << data.observableName;
			}

		};
		class Observable : public CObservable<info>
		{
		public:
			void SetName(std::string const& name)
			{
				m_name = name;
			}
			std::string GetName() const
			{
				return m_name;
			}
		protected:
			info GetChangedData()const override
			{
				info data;
				data.observableName = this->GetName();
				return data;
			}
		private:
			std::string m_name;
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