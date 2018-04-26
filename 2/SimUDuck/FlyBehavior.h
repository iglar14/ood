#pragma once
#include <functional>
#include "CountBehavior.h"

typedef std::function<void()> FlyBehavior;

class FlyWithWings
{
public:
	void operator()()
	{
		std::cout << "I'm flying with wings!! Number: ";
		m_countBehavior.Count();
		std::cout << std::endl;
	}
private:
	CountBehavior m_countBehavior;
};
