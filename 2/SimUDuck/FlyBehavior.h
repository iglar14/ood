#pragma once
#include "CountBehavior.h"

struct IFlyBehavior
{
	virtual ~IFlyBehavior() {};
	virtual void Fly() = 0;
};

typedef std::unique_ptr<IFlyBehavior> IFlyBehaviorPtr;

class FlyWithWings : public IFlyBehavior
{
public:
	void Fly() override
	{
		std::cout << "I'm flying with wings!! Number: ";
		m_countBehavior.Count();
		std::cout << std::endl;
	}
private:
	CountBehavior m_countBehavior;
};

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly() override {}
};
