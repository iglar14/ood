#pragma once

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
		std::cout << "I'm flying with wings!! Number: " << (++m_counter) << std::endl;
	}
private:
	unsigned int m_counter = 0;
};

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly() override {}
};
