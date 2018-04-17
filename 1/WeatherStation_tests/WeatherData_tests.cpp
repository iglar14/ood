#include "stdafx.h"
#include "..\WeatherStation\WeatherData.h"
#include "MockObserver.h"

BOOST_AUTO_TEST_CASE(has_id)
{
	CWeatherDataOut w1("out1");
	CWeatherDataOut w2("out2");
	MockObserver<SWeatherInfoOut> obs1;
	w1.RegisterObserver(obs1);
	w2.RegisterObserver(obs1);

	w1.SetMeasurements(20., 50., 777., 0, 0);
	BOOST_CHECK_EQUAL(obs1.m_data.id, "out1");
	BOOST_CHECK_EQUAL(obs1.m_updateCount, 1);

	w2.SetMeasurements(-10., 90., 777., 0, 0);
	BOOST_CHECK_EQUAL(obs1.m_data.id, "out2");
	BOOST_CHECK_EQUAL(obs1.m_updateCount, 2);
}
