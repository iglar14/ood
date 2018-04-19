#include "stdafx.h"
#include "WeatherData.h"

int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
	CWeatherDataOut wdOut("out");
	CSingleValueDisplay<double> dispTemperature("Temperature");
	wdOut.GetObservableTemperature().RegisterObserver(dispTemperature, 0);

	CSingleValueDisplay<double> dispPressure("Pressure");
	wdOut.GetObservablePressure().RegisterObserver(dispPressure, 0);

	wdOut.SetMeasurements(10., 50., 760., 60., 10.);
	wdOut.SetMeasurements(10., 54., 755., 61., 11.);
	wdOut.SetMeasurements(15., 56., 750., 60., 14.);
	wdOut.SetMeasurements(16., 60., 746., 70., 14.);
	wdOut.SetMeasurements(14., 60., 746., 70., 12.);
	wdOut.SetMeasurements(12., 60., 752., 70., 10.);

	return 0;
}

