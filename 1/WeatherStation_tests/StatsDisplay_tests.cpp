#include "stdafx.h"
#include "..\WeatherStation\WeatherData.h"

SWeatherInfo CreateWeatherInfo(const std::string& id, double temperature, double humidity, double pressure)
{
	SWeatherInfo info;
	info.id = id;
	info.temperature = temperature;
	info.humidity = humidity;
	info.pressure = pressure;
	return info;
}

struct CMockPrinter : public CDummyPrinter
{
	void PrintHeader(const std::string& deviceId) const
	{
		id = deviceId;
		sensors.clear();
	}

	void Print(const std::string& n, const CStats& s) const override
	{
		sensors[n] = s;
	}

	mutable std::map<std::string, CStats> sensors;
	mutable std::string id;
};

BOOST_AUTO_TEST_CASE(groups_statistics_by_id)
{
	auto printer = std::make_shared<CMockPrinter>();
	std::shared_ptr<IObserver<SWeatherInfo>> statsDisplay = std::make_shared<CStatsDisplay>(printer);
	statsDisplay->Update(CreateWeatherInfo("1", 10., 80., 700.));
	
	auto& sensors = printer->sensors;
	BOOST_CHECK_EQUAL(printer->id, "1");
	BOOST_CHECK_EQUAL(sensors["Temp"].GetMax(), 10.);
	BOOST_CHECK_EQUAL(sensors["Temp"].GetMin(), 10.);
	BOOST_CHECK_EQUAL(sensors["Temp"].GetAvg(), 10.);
	BOOST_CHECK_EQUAL(sensors["Hum"].GetMax(), 80.);
	BOOST_CHECK_EQUAL(sensors["Hum"].GetMin(), 80.);
	BOOST_CHECK_EQUAL(sensors["Hum"].GetAvg(), 80.);
	BOOST_CHECK_EQUAL(sensors["Pres"].GetMax(), 700.);
	BOOST_CHECK_EQUAL(sensors["Pres"].GetMin(), 700.);
	BOOST_CHECK_EQUAL(sensors["Pres"].GetAvg(), 700.);

	statsDisplay->Update(CreateWeatherInfo("2", 20., 60., 750.));
	BOOST_CHECK_EQUAL(printer->id, "2");
	BOOST_CHECK_EQUAL(sensors["Temp"].GetMax(), 20.);
	BOOST_CHECK_EQUAL(sensors["Temp"].GetMin(), 20.);
	BOOST_CHECK_EQUAL(sensors["Temp"].GetAvg(), 20.);
	BOOST_CHECK_EQUAL(sensors["Hum"].GetMax(), 60.);
	BOOST_CHECK_EQUAL(sensors["Hum"].GetMin(), 60.);
	BOOST_CHECK_EQUAL(sensors["Hum"].GetAvg(), 60.);
	BOOST_CHECK_EQUAL(sensors["Pres"].GetMax(), 750.);
	BOOST_CHECK_EQUAL(sensors["Pres"].GetMin(), 750.);
	BOOST_CHECK_EQUAL(sensors["Pres"].GetAvg(), 750.);

	statsDisplay->Update(CreateWeatherInfo("1", 0., 100., 600.));
	BOOST_CHECK_EQUAL(printer->id, "1");
	BOOST_CHECK_EQUAL(sensors["Temp"].GetMax(), 10.);
	BOOST_CHECK_EQUAL(sensors["Temp"].GetMin(), 0.);
	BOOST_CHECK_EQUAL(sensors["Temp"].GetAvg(), 5.);
	BOOST_CHECK_EQUAL(sensors["Hum"].GetMax(), 100.);
	BOOST_CHECK_EQUAL(sensors["Hum"].GetMin(), 80.);
	BOOST_CHECK_EQUAL(sensors["Hum"].GetAvg(), 90.);
	BOOST_CHECK_EQUAL(sensors["Pres"].GetMax(), 700.);
	BOOST_CHECK_EQUAL(sensors["Pres"].GetMin(), 600.);
	BOOST_CHECK_EQUAL(sensors["Pres"].GetAvg(), 650.);

	statsDisplay->Update(CreateWeatherInfo("2", 30., 90., 800.));
	BOOST_CHECK_EQUAL(printer->id, "2");
	BOOST_CHECK_EQUAL(sensors["Temp"].GetMax(), 30.);
	BOOST_CHECK_EQUAL(sensors["Temp"].GetMin(), 20.);
	BOOST_CHECK_EQUAL(sensors["Temp"].GetAvg(), 25.);
	BOOST_CHECK_EQUAL(sensors["Hum"].GetMax(), 90.);
	BOOST_CHECK_EQUAL(sensors["Hum"].GetMin(), 60.);
	BOOST_CHECK_EQUAL(sensors["Hum"].GetAvg(), 75.);
	BOOST_CHECK_EQUAL(sensors["Pres"].GetMax(), 800.);
	BOOST_CHECK_EQUAL(sensors["Pres"].GetMin(), 750.);
	BOOST_CHECK_EQUAL(sensors["Pres"].GetAvg(), 775.);
}
