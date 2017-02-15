#include "WeatherData.h"
#include "WeatherDataProDuo.h"

int main()
{
	CWeatherData wd;
	wd.SetName("in");
	CWeatherDataProDuo wdp;
	wdp.SetName("out");

	CDisplay display;
	CDisplayProDuo displayPD;
	CStatsDisplay statsDisplay;
	CStatsDisplayProDuo statsDisplayPD;
	wd.RegisterObserver(display, 1);
	wd.RegisterObserver(statsDisplay, 2);
	wdp.RegisterObserver(displayPD, 1);
	wdp.RegisterObserver(statsDisplayPD, 2);
	
	wd.SetMeasurements(3, 0.7, 760);
	std::cout << "----------------" << std::endl;
	wdp.SetMeasurements(4, 0.8, 761, 30, 40);

	return 0;
}