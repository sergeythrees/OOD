#pragma once
#include <set>
#include <map>
#include <functional>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class InfoEvent
{
public:
	T GetData()
	{
		return m_data;
	}
	void SetData(const T& data)
	{
		m_data = data;
		m_isDataModified = true;
	}
	void SetStatus(bool isDataModified)
	{
		m_isDataModified = isDataModified;
	}
	bool IsModified()
	{
		return m_isDataModified;
	}
private:
	T m_data;
	bool m_isDataModified = false;
};

template <typename T>
class IObservable;

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, const IObservable<T>& observable) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(InfoEvent<T> & event, IObserver<T> & observer) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(InfoEvent<T> & event, IObserver<T> & observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(InfoEvent<T> & event, IObserver<T> & observer) override
	{
		if (m_events.count(&event) > 0)
		{
			m_events.at(&event).emplace(&observer);
		}		
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto eventsCopy = m_events;
		for (auto currentEvent : eventsCopy)
		{
			if ((currentEvent.first)->IsModified())
			{
				for (auto currentObserver : currentEvent.second)
				{
					currentObserver->Update(data, *this);
				}
			}
				
			//(current.second)->Update(data, *this);
		}
	}

	void RemoveObserver(InfoEvent<T> & event, ObserverType & observer) override
	{
		if (m_events.count(&event) != 0)
		{
			m_events.at(&event).erase(&observer);
		}
	}
protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::map<InfoEvent<T>*, std::set<ObserverType *>> m_events;

};
