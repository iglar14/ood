#include "stdafx.h"
#include "..\WeatherStation\WeatherData.h"
#include "MockObserver.h"

BOOST_AUTO_TEST_CASE(has_id)
{
	CWeatherData w1("in");
	CWeatherData w2("out");
	MockObserver<SWeatherInfo> obs1;
	w1.RegisterObserver(obs1);
	w2.RegisterObserver(obs1);

	w1.SetMeasurements(20., 50., 777.);
	BOOST_CHECK_EQUAL(obs1.m_data.id, "in");
	BOOST_CHECK_EQUAL(obs1.m_updateCount, 1);

	w2.SetMeasurements(-10., 90., 777.);
	BOOST_CHECK_EQUAL(obs1.m_data.id, "out");
	BOOST_CHECK_EQUAL(obs1.m_updateCount, 2);
}
