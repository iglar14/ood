#pragma once

class CStats
{
public:
	void operator+=(double val);
	double GetMax() const { return m_max; }
	double GetMin() const { return m_min; }
	double GetAvg() const { return m_acc / m_countAcc; }

private:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_countAcc = 0;
};

class CAnnotatedStats : public CStats
{
public:
	CAnnotatedStats(const std::string& name)
		: m_name(name)
	{}

	void Print();
private:
	std::string m_name;
};