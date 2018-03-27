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
	SWindInfo wind;
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay(const IStatsPrinterPtr& printer);

private:
	struct StatsData
	{
		CStats temperature, humidity, pressure;
		CWindStats wind;
	};
	typedef std::map<std::string, StatsData> StatsMap;	// Statistics from different devices

	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override;
	void UpdateStats(CStats& st, double val, const std::string& name);
	void UpdateStats(CWindStats& st, const SWindInfo& val);

	StatsMap m_stats;
	const IStatsPrinterPtr m_printer;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	CWeatherData(const std::string& id = std::string())
		: m_id(id)
	{}

	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	SWindInfo GetWind()const
	{
		return m_wind;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windDirection, double windSpeed);
protected:
	SWeatherInfo GetChangedData()const override;
private:
	const std::string m_id;
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;
	SWindInfo m_wind;
};
