#pragma once
#include "Observer.h"
#include "Stats.h"

using namespace std;

struct SWindInfo
{
	SWindInfo() = default;
	SWindInfo(double speed, double direction)
		: speed(speed)
		, direction(direction)
	{
	}
	bool operator==(const SWindInfo& other)
	{
		return tie(speed, direction) == tie(other.speed, other.direction);
	}
	bool operator!=(const SWindInfo& other)
	{
		return !(*this == other);
	}
	double speed = 0;
	double direction = 0;	// Degrees
};
struct SWeatherInfo
{
	string id;
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

struct SWeatherInfoIn : public SWeatherInfo
{
};

struct SWeatherInfoOut : public SWeatherInfo
{
	SWindInfo wind;
};

class CDisplay: public IObserver<SWeatherInfoIn>, public IObserver<SWeatherInfoOut>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfoIn const& data) override;
	void Update(SWeatherInfoOut const& data) override;
};

template <typename T>
class CSingleValueDisplay : public IObserver<SValueWithId<T>>
{
public:
	CSingleValueDisplay(const string& name)
		: m_name(name)
	{
	}
	void Update(const SValueWithId<T>& val) override
	{
		if (!val.id.empty())
		{
			cout << "Sensor " << val.id << ": ";
		}
		cout << m_name << " " << val.value << endl;
	}
private:
	string m_name;
};

struct StatsData
{
	CStats temperature, humidity, pressure;
};

typedef StatsData StatsDataIn;

struct StatsDataOut : StatsData
{
	CWindStats wind;
};

template<class Data, class WeatherInfo>
class CStatsDisplayBase : public IObserver<WeatherInfo>
{
public:
	CStatsDisplayBase(const IStatsPrinterPtr& printer)
		: m_printer(printer)
	{
		assert(m_printer);
	}

protected:
	typedef map<string, Data> StatsMap;	// Statistics from different devices

	void UpdateStats(StatsData& stats, const SWeatherInfo& data)
	{
		UpdateStats(stats.temperature, data.temperature, "Temp");
		UpdateStats(stats.humidity, data.humidity, "Hum");
		UpdateStats(stats.pressure, data.pressure, "Pres");
	}
	void UpdateStats(CStats& st, double val, const string& name)
	{
		st += val;
		m_printer->Print(name, st);
	}

	StatsMap m_stats;
	const IStatsPrinterPtr m_printer;
};

class CStatsDisplayIn : public CStatsDisplayBase<StatsDataIn, SWeatherInfoIn>
{
public:
	using CStatsDisplayBase::CStatsDisplayBase;

private:
	void Update(SWeatherInfoIn const& data) override;
};

class CStatsDisplayOut : public CStatsDisplayBase<StatsDataOut, SWeatherInfoOut>
{
public:
	using CStatsDisplayBase::CStatsDisplayBase;

private:
	void Update(SWeatherInfoOut const& data) override;
	void UpdateStats(CWindStats& st, const SWindInfo& val);
};

template <typename T>
class CWeatherDataBase : public CObservable<T>
{
public:
	CWeatherDataBase(const string& id = string())
		: m_id(id)
		, m_temperature(id)
		, m_humidity(id)
		, m_pressure(id)
	{}

	typedef IObservableValue<SValueWithId<double>> ValueObserver;

	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	ValueObserver& GetObservableTemperature()
	{
		return m_temperature;
	}

	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	ValueObserver& GetObservableHumidity()
	{
		return m_humidity;
	}

	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}
	ValueObserver& GetObservablePressure()
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

protected:
	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		MeasurementsChanged();
	}
	virtual T GetChangedData() const override
	{
		T info;
		info.id = GetId();
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
	string GetId() const { return m_id; }
private:
	const string m_id;
	CObservableValue<double> m_temperature = 0.0;
	CObservableValue<double> m_humidity = 0.0;
	CObservableValue<double> m_pressure = 760.0;
};

class CWeatherDataIn : public CWeatherDataBase<SWeatherInfoIn>
{
public:
	using CWeatherDataBase::CWeatherDataBase;
	using CWeatherDataBase::SetMeasurements;
};

class CWeatherDataOut : public CWeatherDataBase<SWeatherInfoOut>
{
public:
	CWeatherDataOut(const string& id = string())
		: CWeatherDataBase<SWeatherInfoOut>(id)
		, m_wind(id)
	{
	}

	SWindInfo GetWind()const
	{
		return m_wind;
	}
	IObservableValue<SValueWithId<SWindInfo>>& GetObservableWind()
	{
		return m_wind;
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windDirection, double windSpeed);
protected:
	SWeatherInfoOut GetChangedData()const override;
private:
	CObservableValue<SWindInfo> m_wind;
};
