#pragma once
#include "stdafx.h"
#include "Observer.h"
#include "CStats.h"
#include "CWindDirection.h"

using namespace std;

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 760.0;
};

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/

	void Update(SWeatherInfo const& data, const IObservable<SWeatherInfo>& observable) override
	{
		std::cout << observable.GetName() << endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
	}

};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(SWeatherInfo const& data, const IObservable<SWeatherInfo>& observable) override
	{
		
		tempStats.Update(data.temperature);
		humStats.Update(data.humidity);
		pressStats.Update(data.pressure);

		std::cout << endl;
		std::cout << observable.GetName() << endl;
		std::cout << "Temperature stats: " << std::endl;
		tempStats.Print();
		std::cout << "Humidify stats: " << std::endl;
		humStats.Print();
		std::cout << "Pressure stats: " << std::endl;
		pressStats.Print();
	}
	Stats<double> tempStats;
	Stats<double> humStats;
	Stats<double> pressStats;
};

template <typename T>
class CWeatherData : public CObservable<T>
{
public:
	// ����������� � �������� �������
	double GetTemperature()const
	{
		return m_temperature;
	}
	// ������������� ��������� (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// ����������� �������� (� ��.��.��)
	double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};
