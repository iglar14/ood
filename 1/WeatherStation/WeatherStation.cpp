#include "stdafx.h"
#include "WeatherData.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CWeatherData wdIn("in"), wdOut("out");
	CDisplay disp;
	wdIn.RegisterObserver(disp, 10);
	wdOut.RegisterObserver(disp, 10);

	CStatsDisplay statd(std::make_shared<CStatsPrinter>());
	wdIn.RegisterObserver(statd, 0);
	wdOut.RegisterObserver(statd, 0);

	wdOut.SetMeasurements(10., 50., 760.);
	wdIn.SetMeasurements(22., 40., 760.);
	wdOut.SetMeasurements(15., 56., 750.);
	wdIn.SetMeasurements(22., 40., 750.);
	wdOut.SetMeasurements(16., 60., 746.);
	wdIn.SetMeasurements(21., 42., 746.);
	wdOut.SetMeasurements(14., 60., 746.);
	wdOut.SetMeasurements(12., 60., 752.);
	wdIn.SetMeasurements(21., 42., 752.);

	return 0;
}

