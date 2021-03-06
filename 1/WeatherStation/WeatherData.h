﻿#pragma once
#include "Observer.h"
#include "Stats.h"

using namespace std;

struct SWeatherInfo
{
	std::string id;
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << data.id << std::endl;
		std::cout << "Current\tTemp\tHum\tPressure\n\t";
		std::cout << data.temperature << '\t';
		std::cout << data.humidity << '\t';
		std::cout << data.pressure << "\t\n";
		std::cout << "----------------\n";
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay(const IStatsPrinterPtr& printer);

private:
	struct StatsData
	{
		CStats temperature, humidity, pressure;
	};
	typedef std::map<std::string, StatsData> StatsMap;	// Statistics from different devices

	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override;
	void UpdateStats(CStats& st, double val, const std::string& name);

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

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.id = m_id;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
private:
	const std::string m_id;
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	
};
