#include "stdafx.h"
#include <iostream>
#include "../WeatherStation/Observer.h"

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(Observervable_class)

	
	BOOST_AUTO_TEST_CASE(should_notify_observers_in_order_of_their_priority)
	{
		class Observer : public IObserver<int>
		{
		public:
			void SetNotificationsOutput(vector<IObserver<int>*>& output)
			{
				m_notificationsOutput = &output;
			}
		private:
			vector<IObserver<int>*>* m_notificationsOutput;
			void Update(const int & data) override
			{
				data;
				m_notificationsOutput->push_back(this);
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

		vector<IObserver<int>*> notifications;
		BOOST_CHECK(notifications == vector<IObserver<int>*>());

		vector<Observer> observers;
		observers.assign(4, Observer());
		for (auto &current : observers)
		{
			current.SetNotificationsOutput(notifications);
		}
		
		Observable observable;
		observable.RegisterObserver(observers[0], 2);
		observable.RegisterObserver(observers[1], 4);
		observable.RegisterObserver(observers[2], 3);
		observable.NotifyObservers();

		BOOST_CHECK(notifications == vector<IObserver<int>*>
			({ &observers[0], &observers[2], &observers[1] }));
		notifications.clear();
		observable.RegisterObserver(observers[3], 1);
		observable.NotifyObservers();
		BOOST_CHECK(notifications == vector<IObserver<int>*>
			({ &observers[3], &observers[0], &observers[2], &observers[1] }));

		BOOST_CHECK(true);
	}
	


BOOST_AUTO_TEST_SUITE_END()