#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

using namespace std;

class WindDirection
{
public:
	WindDirection(unsigned int direction)
	{
		if (direction > 360)
		{
			direction = direction % 360;
		}
		m_direction = direction;
	}
	operator unsigned int()
	{
		return m_direction;
	}
	operator unsigned int() const
	{
		return m_direction;
	}
	WindDirection operator +(WindDirection& second)
	{
		auto result = second.m_direction + this->m_direction;
		if ((second.m_direction - this->m_direction) > 180
			|| (this->m_direction - second.m_direction) > 180)
		{
			result = result - 180;
		}
		return result;
	}
private:
	unsigned int m_direction = 0;
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
		void Update(const double& value)
		{
			if (m_min > value)
			{
				m_min = value;
			}
			if (m_max < value)
			{
				m_max = value;
			}
			m_acc += value;
			++m_countAcc;
			m_average = m_acc / m_countAcc;
		}
		void Update(const WindDirection& direction)
		{
			if (m_directionMin >= direction)
			{
				m_directionMin = direction;
				m_min = m_directionMin;
			}
			if (m_directionMax <= direction)
			{
				m_directionMax = direction;
				m_max = m_directionMax;
			}
			m_directionAcc = m_directionAcc + direction;
			++m_countAcc;
			m_average = m_directionAcc / m_countAcc;
		}
		void Print()
		{
			std::cout << "	max : " << m_max << std::endl;
			std::cout << "	min : " << m_min << std::endl;
			std::cout << "	average : " << m_average << std::endl;
		}
	private:
		double m_min = std::numeric_limits<double>::infinity();
		double m_max = -std::numeric_limits<double>::infinity();
		unsigned int m_directionMin = 360;
		unsigned int m_directionMax = 0;
		WindDirection m_directionAcc = 0;
		double m_average = 0;
		double m_acc = 0;
		unsigned m_countAcc = 0;
	};
	
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
	Stats tempStats;
	Stats humStats;
	Stats pressStats;
	Stats windSpeed;
	Stats windDir;

	
	

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
