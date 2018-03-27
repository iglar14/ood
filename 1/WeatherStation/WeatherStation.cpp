#include "stdafx.h"
#include "WeatherData.h"

int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
	CWeatherData wdOut("out");
	CDisplay disp;
	wdOut.RegisterObserver(disp, 0);

	CStatsDisplay statd(std::make_shared<CStatsPrinter>());
	wdOut.RegisterObserver(statd, 0);

	wdOut.SetMeasurements(10., 50., 760., 60., 10.);
	wdOut.SetMeasurements(15., 56., 750., 60., 14.);
	wdOut.SetMeasurements(16., 60., 746., 70., 14.);
	wdOut.SetMeasurements(14., 60., 746., 70., 12.);
	wdOut.SetMeasurements(12., 60., 752., 70., 10.);

	return 0;
}

