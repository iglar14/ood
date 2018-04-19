#pragma once
#include "Observer.h"
#include "Stats.h"

using namespace std;

struct SWindInfo
{
	double speed = 0;
	double direction = 0;	// Degrees
};
struct SWeatherInfo
{
	std::string id;
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
	typedef std::map<std::string, Data> StatsMap;	// Statistics from different devices

	void UpdateStats(StatsData& stats, const SWeatherInfo& data)
	{
		UpdateStats(stats.temperature, data.temperature, "Temp");
		UpdateStats(stats.humidity, data.humidity, "Hum");
		UpdateStats(stats.pressure, data.pressure, "Pres");
	}
	void UpdateStats(CStats& st, double val, const std::string& name)
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
	CWeatherDataBase(const std::string& id = std::string())
		: m_id(id)
	{}

	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	IObservableValue<double>& GetObservableTemperature()
	{
		return m_temperature;
	}

	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	IObservableValue<double>& GetObservableHumidity()
	{
		return m_humidity;
	}

	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}
	IObservableValue<double>& GetObservablePressure()
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
	std::string GetId() const { return m_id; }
private:
	const std::string m_id;
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
	using CWeatherDataBase::CWeatherDataBase;

	SWindInfo GetWind()const
	{
		return m_wind;
	}
	IObservableValue<SWindInfo>& GetObservableWind()
	{
		return m_wind;
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windDirection, double windSpeed);
protected:
	SWeatherInfoOut GetChangedData()const override;
private:
	CObservableValue<SWindInfo> m_wind;
};
