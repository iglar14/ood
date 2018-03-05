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

void CAnnotatedStats::PrintHeader()
{
	std::cout << "\tMax\tMin\tAverage\n";
}

void CAnnotatedStats::Print() const
{
	const char* name = m_name.c_str();
	std::cout << name << "\t" << GetMax() << "\t" << GetMin() << "\t" << GetAvg() << std::endl;
}