#pragma once
#include "FlyBehavior.h"
#include "QuackBehavior.h"
#include "DanceBehavior.h"

class Duck
{
public:
	Duck(IFlyBehaviorPtr&& flyBehavior,
		IQuackBehaviorPtr&& quackBehavior,
		IDanceBehaviorPtr&& danceBehavior = nullptr);
	void Quack() const;
	void Swim();
	void Fly();
	void Dance();
	void SetFlyBehavior(IFlyBehaviorPtr&& flyBehavior);
	void SetDanceBehavior(IDanceBehaviorPtr&& danceBehavior);

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	IFlyBehaviorPtr m_flyBehavior;
	IQuackBehaviorPtr m_quackBehavior;
	IDanceBehaviorPtr m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck();
	void Display() const override;
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck();
	void Display() const override;
};
class DeckoyDuck : public Duck
{
public:
	DeckoyDuck();
	void Display() const override;
};
class RubberDuck : public Duck
{
public:
	RubberDuck();
	void Display() const override;
};

class ModelDuck : public Duck
{
public:
	ModelDuck();
	void Display() const override;
};
