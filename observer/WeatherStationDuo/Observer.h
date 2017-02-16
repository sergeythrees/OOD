﻿#pragma once

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
	virtual void RegisterObserver(IObserver<T> & observer, unsigned int priority = 0) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer, unsigned int priority) override
	{
		if (m_observers.count(&observer) > 0)
		{
			RemoveObserver(observer);
		}
		m_observers.emplace(&observer);
		m_priorities.emplace(priority, &observer);
		
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto prioritiesCopy = m_priorities;
		for (auto current : prioritiesCopy)
		{
			(current.second)->Update(data, *this);
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		m_observers.erase(&observer);
		for (auto current : m_priorities)
		{
			if (current.second == &observer)
			{
				m_priorities.erase(current.first);
				break;
			}
		}
	}
protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::set<ObserverType *> m_observers;
	std::multimap<unsigned int, ObserverType *> m_priorities;

};
