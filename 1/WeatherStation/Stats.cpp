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

double CStats::GetAvg() const
{
	return (m_countAcc > 0) ? m_acc / m_countAcc : 0;
}

void CStats::operator+=(double val)
{
	m_minmax += val;
	m_acc += val;
	++m_countAcc;
}

void CWindStats::operator+=(const SWindInfo& wind)
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
	if (m_countAcc > 0)
	{
		info.direction = RadToDeg(atan2(m_accY, m_accX));
		info.speed = sqrt(m_accX * m_accX + m_accY * m_accY) / m_countAcc;
	}
	return info;
}

void CStatsPrinter::PrintHeader(const std::string& id) const
{
	cout << id.c_str() << "\tMax\tMin\tAverage\n";
}

void CStatsPrinter::Print(const std::string& name, const CStats& stats) const
{
	const char* pName = name.c_str();
	cout << pName << "\t" << stats.GetMax() << "\t" << stats.GetMin() << "\t" << stats.GetAvg() << std::endl;
}

void CStatsPrinter::Print(const std::string& name, const CWindStats& stats) const
{
	const char* pName = name.c_str();
	cout << pName << "\t" << stats.GetMax() << "\t" << stats.GetMin() << "\t";
	SWindInfo windInfo = stats.GetAvg();
	cout << "Direction: " << windInfo.direction << " Speed: " << windInfo.speed << std::endl;
}

void CStatsPrinter::PrintBottom() const
{
	cout << "------\n";
};
