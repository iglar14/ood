#pragma once

struct ICountBehavior
{
	virtual ~ICountBehavior() {};
	virtual void Count() = 0;
};

class CountBehavior : public ICountBehavior
{
public:
	void Count() override
	{
		std::cout << ++m_counter;
	}
private:
	unsigned int m_counter = 0;
};

class NoCountBehavior : public ICountBehavior
{
public:
	void Count() override {}
};
