#include "stdafx.h"
#include "WeatherData.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CWeatherData wd;
	CDisplay disp;
	wd.RegisterObserver(disp);

	CStatsDisplay statd;
	wd.RegisterObserver(statd);

	wd.SetMeasurements(10., 50., 760.);
	wd.SetMeasurements(15., 56., 750.);

	return 0;
}

