#include "stdafx.h"
#include "Stats.h"

void CStats::operator+=(double val)
{
	if (m_min > val)
	{
		m_min = val;
	}
	if (m_max < val)
	{
		m_max = val;
	}
	m_acc += val;
	++m_countAcc;
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
