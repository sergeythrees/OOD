#include "WeatherData.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display, 1);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 2);

	wd.SetMeasurements(3, 0.7, 760, 20, 360);
	std::cout << "----------------" << std::endl;
	wd.SetMeasurements(4, 0.8, 761, 30, 40);
	std::cout << "----------------" << std::endl;
	wd.SetMeasurements(10, 0.8, 761, 80, 80);
	std::cout << "----------------" << std::endl;
	wd.SetMeasurements(-10, 0.8, 761, 160, 160);

	return 0;
}