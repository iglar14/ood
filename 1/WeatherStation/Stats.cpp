#include "stdafx.h"
#include "Stats.h"
#include "WeatherData.h"

static double DegToRad(double a)
{
	return a * (M_PI / 180.);
}

static double RadToDeg(double a)
{
	return a * (180. / M_PI);
}

void SMinMax::operator +=(double val)
{
	if (min > val)
	{
		min = val;
	}
	if (max < val)
	{
		max = val;
	}
}

void CStats::operator+=(double val)
{
	m_minmax += val;
	m_acc += val;
	++m_countAcc;
}

void CWindStats::operator+=(SWindInfo& wind)
{
	m_minmaxSpeed += wind.speed;
	const double x = cos(DegToRad(wind.direction)) * wind.speed;
	const double y = sin(DegToRad(wind.direction)) * wind.speed;
	m_accX += x;
	m_accY += y;
	++m_countAcc;
}

SWindInfo CWindStats::GetAvg() const
{
	SWindInfo info;
	info.direction = RadToDeg(atan2(m_accY, m_accX));
	info.speed = sqrt(m_accX * m_accX + m_accY * m_accY) / m_countAcc;
	return info;
}

void CStatsPrinter::PrintHeader(const std::string& id) const
{
	std::cout << id.c_str() << "\tMax\tMin\tAverage\n";
}

void CStatsPrinter::Print(const std::string& name, const CStats& stats) const
{
	const char* pName = name.c_str();
	std::cout << pName << "\t" << stats.GetMax() << "\t" << stats.GetMin() << "\t" << stats.GetAvg() << std::endl;
}

void CStatsPrinter::PrintBottom() const
{
	std::cout << "------\n";
};
