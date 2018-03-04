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

void CAnnotatedStats::Print()
{
	const char* name = m_name.c_str();
	std::cout << "Max " << name << " " << GetMax() << std::endl;
	std::cout << "Min " << name << " " << GetMin() << std::endl;
	std::cout << "Average " << name << " " << GetAvg() << std::endl;
}