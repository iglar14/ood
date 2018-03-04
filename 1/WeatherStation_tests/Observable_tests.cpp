#include "stdafx.h"
#include "..\WeatherStation\Observer.h"

class TestObservable : public CObservable<int>
{
public:
	void SetData(int data)
	{
		if (data != m_data)
		{
			m_data = data;
			NotifyObservers();
		}
	}
protected:
	virtual int GetChangedData()const
	{
		return m_data;
	}
private:
	int m_data = 42;
};

class TestObserver : public IObserver<int>
{
public:
	TestObserver(TestObservable& observable)
		: m_observable(observable)
	{}

	bool m_shouldRemove = false;
	int m_updateCount = 0;
	int m_data = 0;
private:
	void Update(const int& data)
	{
		m_data = data;
		if (m_shouldRemove)
		{
			m_observable.RemoveObserver(*this);
		}
		++m_updateCount;
	}
	TestObservable& m_observable;
};

BOOST_AUTO_TEST_CASE(Notofies_observers)
{
	TestObservable o;
	TestObserver obs1(o), obs2(o);
	o.SetData(13);
	BOOST_CHECK_EQUAL(obs1.m_data, 0);
	BOOST_CHECK_EQUAL(obs1.m_updateCount, 0);
	BOOST_CHECK_EQUAL(obs2.m_data, 0);
	BOOST_CHECK_EQUAL(obs2.m_updateCount, 0);

	o.RegisterObserver(obs1);
	o.SetData(14);
	BOOST_CHECK_EQUAL(obs1.m_data, 14);
	BOOST_CHECK_EQUAL(obs1.m_updateCount, 1);
	BOOST_CHECK_EQUAL(obs2.m_data, 0);
	BOOST_CHECK_EQUAL(obs2.m_updateCount, 0);

	o.SetData(15);
	BOOST_CHECK_EQUAL(obs1.m_data, 15);
	BOOST_CHECK_EQUAL(obs1.m_updateCount, 2);
	BOOST_CHECK_EQUAL(obs2.m_data, 0);
	BOOST_CHECK_EQUAL(obs2.m_updateCount, 0);

	o.RegisterObserver(obs2);
	o.SetData(14);
	BOOST_CHECK_EQUAL(obs1.m_data, 14);
	BOOST_CHECK_EQUAL(obs1.m_updateCount, 3);
	BOOST_CHECK_EQUAL(obs2.m_data, 14);
	BOOST_CHECK_EQUAL(obs2.m_updateCount, 1);
}

BOOST_AUTO_TEST_CASE(Can_unsubscribe_during_update)
{
	TestObservable o;
	TestObserver obs1(o), obs2(o), obs3(o);
	o.RegisterObserver(obs1);
	o.RegisterObserver(obs2);
	o.RegisterObserver(obs3);

	obs1.m_shouldRemove = true;
	o.SetData(11);

	BOOST_CHECK_EQUAL(obs1.m_data, 11);
	BOOST_CHECK_EQUAL(obs1.m_updateCount, 1);

	BOOST_CHECK_EQUAL(obs2.m_data, 11);
	BOOST_CHECK_EQUAL(obs2.m_updateCount, 1);

	BOOST_CHECK_EQUAL(obs3.m_data, 11);
	BOOST_CHECK_EQUAL(obs3.m_updateCount, 1);
}