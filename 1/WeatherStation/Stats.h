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

class IStatsPrinter
{
public:
	virtual ~IStatsPrinter() = default;

	virtual void PrintHeader(const std::string& id) const = 0;
	virtual void Print(const std::string& name, const CStats&) const = 0;
	virtual void PrintBottom() const = 0;
};

typedef std::shared_ptr<IStatsPrinter> IStatsPrinterPtr;

class CStatsPrinter : public IStatsPrinter
{
public:
	void PrintHeader(const std::string& id) const override;
	void Print(const std::string& name, const CStats& stats) const override;
	void PrintBottom() const override;
};

class CDummyPrinter : public IStatsPrinter
{
	void PrintHeader(const std::string&) const override {};
	void Print(const std::string&, const CStats&) const override {};
	void PrintBottom() const override {};
};