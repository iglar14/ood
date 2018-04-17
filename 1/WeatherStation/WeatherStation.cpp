#include "stdafx.h"
#include "WeatherData.h"

int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
	CWeatherDataIn wdIn("in");
	CWeatherDataOut wdOut("out");
	CDisplay disp;
	wdIn.RegisterObserver(disp, 0);
	wdOut.RegisterObserver(disp, 0);

	CStatsDisplayIn statdIn(std::make_shared<CStatsPrinter>());
	wdIn.RegisterObserver(statdIn, 0);
	CStatsDisplayOut statdOut(std::make_shared<CStatsPrinter>());
	wdOut.RegisterObserver(statdOut, 0);

	wdIn.SetMeasurements(22., 40., 760.);
	wdOut.SetMeasurements(10., 50., 760., 60., 10.);
	wdOut.SetMeasurements(15., 56., 750., 60., 14.);
	wdIn.SetMeasurements(23., 35., 750.);
	wdOut.SetMeasurements(16., 60., 746., 70., 14.);
	wdIn.SetMeasurements(23., 35., 746.);
	wdOut.SetMeasurements(14., 60., 746., 70., 12.);
	wdOut.SetMeasurements(12., 60., 752., 70., 10.);
	wdIn.SetMeasurements(21., 45., 752.);

	return 0;
}

