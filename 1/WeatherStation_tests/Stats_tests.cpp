#include "stdafx.h"
#include "..\WeatherStation\WeatherData.h"
#include "..\WeatherStation\Stats.h"

static void CheckWindInfo(const SWindInfo& wi, double direction, double speed)
{
	BOOST_CHECK_CLOSE(wi.direction, direction, 0.01);
	BOOST_CHECK_CLOSE(wi.speed, speed, 0.01);
}

BOOST_AUTO_TEST_CASE(WindStats_stores_min_max_wind_values)
{
	CWindStats stats;
	SWindInfo wi;
	wi.speed = 10;
	stats += wi;
	wi.speed = -10;
	wi.direction = 100;
	stats += wi;
	BOOST_CHECK_EQUAL(stats.GetMax(), 10.);
	BOOST_CHECK_EQUAL(stats.GetMin(), -10.);
}

BOOST_AUTO_TEST_CASE(WindStats_calculates_wind_average)
{
	CWindStats stats;

	CheckWindInfo(stats.GetAvg(), 0, 0);

	SWindInfo wi;
	wi.speed = 10;
	stats += wi;
	CheckWindInfo(stats.GetAvg(), 0, 10.);

	wi.speed = 10;
	stats += wi;
	CheckWindInfo(stats.GetAvg(), 0, 10.);

	wi.speed = 1;
	stats += wi;
	CheckWindInfo(stats.GetAvg(), 0, 7.);

	wi.speed = 21;
	wi.direction = 120;
	stats += wi;
	CheckWindInfo(stats.GetAvg(), 60., 5.25);
}
