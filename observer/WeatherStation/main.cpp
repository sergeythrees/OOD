#include "WeatherData.h"

int main()
{
	CWeatherData in;
	CWeatherData out;
	CDisplay display;
	
	in.SetName("in");
	out.SetName("out");
	in.RegisterObserver(display,  1);
	out.RegisterObserver(display, 1);
	in.SetMeasurements(12, 4, 5);
	out.SetMeasurements(0, 2, 4);

	return 0;
}