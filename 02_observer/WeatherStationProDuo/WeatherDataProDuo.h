#pragma once
#include "stdafx.h"
#include "Observer.h"
#include "CStats.h"
#include "CWindDirection.h"
#include "WeatherData.h"

using namespace std;

struct SWeatherInfoPro : public SWeatherInfo
{
	double windSpeed = 0;
	WindDirection windDirection = 0;
};

class CDisplayProDuo: public IObserver<SWeatherInfoPro>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/

	void Update(SWeatherInfoPro const& data, const IObservable<SWeatherInfoPro>& observable) override
	{
		std::cout << endl;
		std::cout << observable.GetName() << endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
		std::cout << "Current Wind Direction " << data.windDirection << std::endl;
	}

};

class CStatsDisplayProDuo : public IObserver<SWeatherInfoPro>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfoPro const& data, const IObservable<SWeatherInfoPro>& observable) override
	{
		tempStats.Update(data.temperature);
		humStats.Update(data.humidity);
		pressStats.Update(data.pressure);
		windSpeed.Update(data.windSpeed);
		windDir.Update(data.windDirection);

		std::cout << endl;
		std::cout << observable.GetName() << endl;
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

class WeatherData : public CWeatherData<SWeatherInfo>
{
public:
	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

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
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

class CWeatherDataProDuo : public CWeatherData<SWeatherInfoPro>
{
public:
	double GetWindSpeed()const
	{
		return m_windSpeed;
	}
	WindDirection GetWindDirection()const
	{
		return m_windDirection;
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
	SWeatherInfoPro GetChangedData()const override
	{
		SWeatherInfoPro info;
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
