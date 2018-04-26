#pragma once
struct IQuackBehavior
{
	virtual ~IQuackBehavior() {};
	virtual void Quack() = 0;
};

typedef std::unique_ptr<IQuackBehavior> IQuackBehaviorPtr;

class QuackBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		std::cout << "Quack Quack!!!" << std::endl;
	}
};
class SqueakBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		std::cout << "Squeek!!!" << std::endl;
	}
};

class MuteQuackBehavior : public IQuackBehavior
{
public:
	void Quack() override {}
};
