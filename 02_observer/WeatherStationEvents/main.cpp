#include "WeatherData.h"

int main()
{
	CWeatherData in;
	CWeatherData out;
	CDisplay display;
	InfoEvent<SWeatherInfo> info1;
	
	in.SetName("in");
	out.SetName("out");
	in.RegisterObserver(info1, display);
	out.RegisterObserver(info1, display);
	in.SetMeasurements(12, 4, 5);
	out.SetMeasurements(0, 2, 4);

	return 0;
}