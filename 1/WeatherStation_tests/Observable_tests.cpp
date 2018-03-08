#include "stdafx.h"
#include "MockObserver.h"

typedef MockObserver<int> TestObserver;

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
	int m_data = 0;
};

BOOST_AUTO_TEST_CASE(Notofies_observers)
{
	TestObservable o;
	TestObserver obs1(0), obs2(0);
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
	TestObserver obs1(0), obs2(0), obs3(0);
	o.RegisterObserver(obs1);
	o.RegisterObserver(obs2);
	o.RegisterObserver(obs3);

	obs1.m_updateAction = [&](TestObserver* observer) { o.RemoveObserver(*observer); };
	o.SetData(11);

	BOOST_CHECK_EQUAL(obs1.m_data, 11);
	BOOST_CHECK_EQUAL(obs1.m_updateCount, 1);

	BOOST_CHECK_EQUAL(obs2.m_data, 11);
	BOOST_CHECK_EQUAL(obs2.m_updateCount, 1);

	BOOST_CHECK_EQUAL(obs3.m_data, 11);
	BOOST_CHECK_EQUAL(obs3.m_updateCount, 1);
}

BOOST_AUTO_TEST_CASE(Orders_by_priority)
{
	TestObservable observable;
	TestObserver obs1, obs2, obs3, obs4, obs5, obs6;
	std::vector<TestObserver*> updates;
	obs1.m_updateAction = obs2.m_updateAction = obs3.m_updateAction = obs4.m_updateAction = obs5.m_updateAction = obs6.m_updateAction
		= [&](TestObserver* o) { updates.push_back(o); };
	observable.RegisterObserver(obs1, 30);
	observable.RegisterObserver(obs2, 0);
	observable.RegisterObserver(obs3, 10);
	observable.RegisterObserver(obs4, 0);
	observable.RegisterObserver(obs5, 10);
	observable.RegisterObserver(obs6, 30);

	observable.SetData(11);

	BOOST_CHECK_EQUAL(updates.size(), 6u);
	BOOST_CHECK_EQUAL(updates[0], &obs2);
	BOOST_CHECK_EQUAL(updates[1], &obs4);
	BOOST_CHECK_EQUAL(updates[2], &obs3);
	BOOST_CHECK_EQUAL(updates[3], &obs5);
	BOOST_CHECK_EQUAL(updates[4], &obs1);
	BOOST_CHECK_EQUAL(updates[5], &obs6);
}