#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"
#include "CWindDirection.h"

using namespace std;

template <typename T>
class Stats
{
public:
	double GetMin()
	{
		return m_min;
	}
	double GetMax()
	{
		return m_max;
	}
	double GetAverage()
	{
		return m_average;
	}
	void Update(const T& value)
	{
		if (m_min > value)
		{
			m_min = value;
		}
		if (m_max < value)
		{
			m_max = value;
		}
		m_acc = m_acc + value;
		++m_countAcc;
		m_average = m_acc / m_countAcc;
	}
	void Print()
	{
		std::cout << "	max : " << m_max << std::endl;
		std::cout << "	min : " << m_min << std::endl;
		std::cout << "	average : " << m_average << std::endl;
	}
private:
	double m_min = std::numeric_limits<double>::infinity();;
	double m_max = -std::numeric_limits<double>::infinity();;
	double m_average = 0;
	T m_acc = 0;
	unsigned m_countAcc = 0;
};


struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	WindDirection windDirection = 0;
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/

	void Update(SWeatherInfo const& data) override
	{
		std::cout << endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
		std::cout << "Current Wind Direction " << data.windDirection << std::endl;
	}

};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:	
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		tempStats.Update(data.temperature);
		humStats.Update(data.humidity);
		pressStats.Update(data.pressure);
		windSpeed.Update(data.windSpeed);
		windDir.Update(data.windDirection);

		std::cout << endl;
		std::cout << "Temperature stats: " << std::endl;
		tempStats.Print();
		std::cout << "Humidify stats: " << std::endl;
		humStats.Print();
		std::cout << "Pressure stats: " << std::endl;
		pressStats.Print();
		std::cout << "Wind Speed stats: " << std::endl;
		windSpeed.Print();
		std::cout << "Wind Direction stats: " << std::endl;
		windDir.Print();
	}
	Stats<double> tempStats;
	Stats<double> humStats;
	Stats<double> pressStats;
	Stats<double> windSpeed;
	Stats<WindDirection> windDir;
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
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}
	double GetWindSpeed()const
	{
		return m_windSpeed;
	}
	WindDirection GetWindDirection()const
	{
		return m_windDirection;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, 
		double windSpeed, WindDirection windDirection)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windSpeed = windSpeed;
		m_windDirection = windDirection;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windSpeed = GetWindSpeed();
		info.windDirection = GetWindDirection();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	
	double m_windSpeed = 0;
	WindDirection m_windDirection = 0;
};
