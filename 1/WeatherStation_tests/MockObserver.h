#pragma once
#include "..\WeatherStation\Observer.h"

template<typename T>
class MockObserver : public IObserver<T>
{
public:
	MockObserver() = default;
	MockObserver(const T& initialData)
		: m_data(initialData)
	{}

	std::function<void(MockObserver*)> m_updateAction;
	int m_updateCount = 0;
	T m_data;
private:
	void Update(const T& data)
	{
		m_data = data;
		if (m_updateAction)
		{
			m_updateAction(this);
		}
		++m_updateCount;
	}
};