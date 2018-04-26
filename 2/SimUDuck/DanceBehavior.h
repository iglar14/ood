#pragma once
struct IDanceBehavior
{
	virtual ~IDanceBehavior() = default;
	virtual void Dance() const = 0;
};

typedef std::unique_ptr<IDanceBehavior> IDanceBehaviorPtr;

class WaltzDance : public IDanceBehavior
{
	virtual void Dance() const
	{
		std::cout << "Dancing Waltz" << std::endl;
	}
};

class MinuetDance : public IDanceBehavior
{
	virtual void Dance() const
	{
		std::cout << "Dancing Minuet" << std::endl;
	}
};

class NoDance : public IDanceBehavior
{
	virtual void Dance() const {}
};
