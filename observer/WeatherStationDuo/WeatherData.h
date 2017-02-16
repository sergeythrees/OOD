#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include "Observer.h"

using namespace std;

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/

	void Update(SWeatherInfo const& data, const IObservable<SWeatherInfo>& observable) override
	{
		std::cout << observable.GetName() << endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}

};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	class Stats
	{
	public:
		double min = std::numeric_limits<double>::infinity();
		double max = -std::numeric_limits<double>::infinity();
		double average = 0;
		void Update(const double& value)
		{
			if (min > value)
			{
				min = value;
			}
			if (max < value)
			{
				max = value;
			}
			m_acc += value;
			++m_countAcc;
			average = m_acc / m_countAcc;
		}
		void Print()
		{
			std::cout << "	max : " << max << std::endl;
			std::cout << "	min : " << min << std::endl;
			std::cout << "	average : " << average << std::endl;
		}
	private:
		double m_acc = 0;
		unsigned m_countAcc = 0;
	};
	
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data, const IObservable<SWeatherInfo>& observable) override
	{
		tempStats.Update(data.temperature);
		humStats.Update(data.humidity);
		pressStats.Update(data.pressure);

		std::cout << observable.GetName() << endl;
		std::cout << "Temperature stats: " << std::endl;
		tempStats.Print();
		std::cout << "Humidify stats: " << std::endl;
		humStats.Print();
		std::cout << "Pressure stats: " << std::endl;
		pressStats.Print();
	}
	Stats tempStats;
	Stats humStats;
	Stats pressStats;

	
	

};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		humidity = humidity;
		m_temperature = temp;
		pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
private:
	double m_temperature = 0.0;
	double humidity = 0.0;	
	double pressure = 760.0;	
};
