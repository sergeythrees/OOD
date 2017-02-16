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
	virtual void RegisterObserver(IObserver<T> & observer, unsigned int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
	virtual std::string GetName() const = 0;
	virtual void SetName(const std::string& name) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer, unsigned int priority) override
	{
		if (m_observers.count(&observer) == 0)
		{
			m_observers.insert(&observer);
			m_priorities.emplace(priority, &observer);
		}
		
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		for (auto current : m_priorities)
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
	void SetName(std::string const& name) override
	{
		m_name = name;
	}
	std::string GetName() const override
	{
		return m_name;
	}
protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::string m_name;
	std::set<ObserverType *> m_observers;
	std::map<unsigned int, ObserverType *> m_priorities;
};
