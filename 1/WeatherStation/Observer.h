#pragma once

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer, int priority = 0) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;
	struct observer {};
	struct priority {};
	typedef boost::bimap<boost::bimaps::tagged<ObserverType*, observer>, boost::bimaps::multiset_of<boost::bimaps::tagged<int, priority>>> observers_bimap;

	void RegisterObserver(ObserverType & obs, int pr = 0) override
	{
		m_observers.insert({ &obs, pr });
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		const auto observers = m_observers;
		for (auto iter = observers.by<priority>().begin(); iter != observers.by<priority>().end(); ++iter)
		{
			iter->get<observer>()->Update(data);
		}
	}

	void RemoveObserver(ObserverType& obs) override
	{
		m_observers.by<observer>().erase(&obs);
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	observers_bimap m_observers;
};
