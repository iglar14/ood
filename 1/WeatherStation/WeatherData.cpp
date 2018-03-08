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
	m_printer->PrintBottom();
}

void CStatsDisplay::UpdateStats(CStats& st, double val, const std::string& name)
{
	st += val;
	m_printer->Print(name, st);
}
