#include "stdafx.h"
#include <iostream>
#include "../WeatherStation/Observer.h"

using namespace std;
using namespace boost;


class Observable : public CObservable<int>
{
protected:
	int GetChangedData()const override
	{
		return 0;
	}
};

namespace NotificationsSafety
{
	class Observer : public IObserver<int>
	{
	public:
		void SetObserverAndObservableForRemove(Observer& observer, Observable& observable)
		{
			m_observerForRemove = &observer;
			m_observableForRemove = &observable;
		}
	private:
		Observer* m_observerForRemove;
		Observable* m_observableForRemove;
		void Update(const int & data) override
		{
			data;
			m_observableForRemove->RemoveObserver(*m_observerForRemove);
		}
	};
	void CheckNotifyMethodForSafety(Observer& a, Observer& b)
	{
		Observable observable;
		observable.RegisterObserver(a, 0);
		observable.RegisterObserver(b, 1);
		a.SetObserverAndObservableForRemove(a, observable);
		b.SetObserverAndObservableForRemove(b, observable);
		
		BOOST_CHECK_NO_THROW(observable.NotifyObservers());
		BOOST_CHECK_NO_THROW(observable.NotifyObservers());
	}


}


BOOST_AUTO_TEST_SUITE(Observervable_class)

	BOOST_AUTO_TEST_SUITE(NotifyObservers_method)
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
		}
	
			BOOST_AUTO_TEST_CASE(should_work_safe_when_one_observer_remove_another_observer_while_updating)
			{
				NotificationsSafety::Observer observer1;
				NotificationsSafety::Observer observer2;

				NotificationsSafety::CheckNotifyMethodForSafety(observer1, observer2);
				NotificationsSafety::CheckNotifyMethodForSafety(observer1, observer1);
				NotificationsSafety::CheckNotifyMethodForSafety(observer2, observer2);
				NotificationsSafety::CheckNotifyMethodForSafety(observer2, observer1);
			}
		BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()