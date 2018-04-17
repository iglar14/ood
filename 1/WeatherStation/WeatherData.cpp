#include "stdafx.h"
#include "WeatherData.h"

void CStatsDisplayIn::Update(SWeatherInfoIn const& data)
{
	StatsDataIn& stats = m_stats[data.id];
	m_printer->PrintHeader(data.id);
	CStatsDisplayBase::UpdateStats(stats, data);
	m_printer->PrintBottom();
}

void CStatsDisplayOut::Update(SWeatherInfoOut const& data)
{
	StatsDataOut& stats = m_stats[data.id];
	m_printer->PrintHeader(data.id);
	CStatsDisplayBase::UpdateStats(stats, data);
	UpdateStats(stats.wind, data.wind);
	m_printer->PrintBottom();
}

void CStatsDisplayOut::UpdateStats(CWindStats& st, const SWindInfo& val)
{
	st += val;
	m_printer->Print("Wind", st);
}

void CDisplay::Update(SWeatherInfoIn const& data)
{
	cout << data.id << std::endl;
	cout << "Current\tTemp\tHum\tPres\n\t";
	cout << data.temperature << '\t';
	cout << data.humidity << '\t';
	cout << data.pressure << "\t\t";
	cout << "----------------\n";
}

void CDisplay::Update(SWeatherInfoOut const& data)
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

SWeatherInfoOut CWeatherDataOut::GetChangedData()const
{
	SWeatherInfoOut info = CWeatherDataBase::GetChangedData();
	info.wind = GetWind();
	return info;
}
