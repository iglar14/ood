#include "stdafx.h"
#include "WeatherData.h"

CStatsDisplay::CStatsDisplay(const IStatsPrinterPtr& printer)
	: m_printer(printer)
{
	assert(m_printer);
}

void CStatsDisplay::Update(SWeatherInfo const& data)
{
	StatsData& stats = m_stats[data.id];
	m_printer->PrintHeader(data.id);
	UpdateStats(stats.temperature, data.temperature, "Temp");
	UpdateStats(stats.humidity, data.humidity, "Hum");
	UpdateStats(stats.pressure, data.pressure, "Pres");
	UpdateStats(stats.wind, data.wind);
	m_printer->PrintBottom();
}

void CStatsDisplay::UpdateStats(CStats& st, double val, const std::string& name)
{
	st += val;
	m_printer->Print(name, st);
}

void CStatsDisplay::UpdateStats(CWindStats& st, const SWindInfo& val)
{
	st += val;
	m_printer->Print("Wind", st);
}

void CDisplayIn::Update(SWeatherInfoIn const& data)
{
	cout << data.id << std::endl;
	cout << "Current\tTemp\tHum\tPres\tWind direction\tspeed\n\t";
	cout << data.temperature << '\t';
	cout << data.humidity << '\t';
	cout << data.pressure << "\t\t";
	cout << "----------------\n";
}

void CDisplayOut::Update(SWeatherInfoOut const& data)
{
	cout << data.id << std::endl;
	cout << "Current\tTemp\tHum\tPres\tWind direction\tspeed\n\t";
	cout << data.temperature << '\t';
	cout << data.humidity << '\t';
	cout << data.pressure << "\t\t";
	cout << data.wind.direction << "\t";
	cout << data.wind.speed << "\t\n";
	cout << "----------------\n";
}

void CWeatherDataOut::SetMeasurements(double temp, double humidity, double pressure, double windDirection, double windSpeed)
{
	m_wind.direction = windDirection;
	m_wind.speed = windSpeed;

	CWeatherDataBase::SetMeasurements(temp, humidity, pressure);
}

SWeatherInfoIn CWeatherDataIn::GetChangedData()const
{
	SWeatherInfoIn info;
	info.id = GetId();
	info.temperature = GetTemperature();
	info.humidity = GetHumidity();
	info.pressure = GetPressure();
	return info;
}

SWeatherInfoOut CWeatherDataOut::GetChangedData()const
{
	SWeatherInfoOut info;
	info.id = GetId();
	info.temperature = GetTemperature();
	info.humidity = GetHumidity();
	info.pressure = GetPressure();
	info.wind = GetWind();
	return info;
}
