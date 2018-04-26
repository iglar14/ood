#include <cassert>
#include <iostream>
#include <memory>
// #include <vector>
#include "Ducks.h"

using namespace std;

Duck::Duck(IFlyBehaviorPtr&& flyBehavior,
		IQuackBehaviorPtr&& quackBehavior,
		IDanceBehaviorPtr&& danceBehavior)
		: m_quackBehavior(move(quackBehavior))
		, m_danceBehavior(move(danceBehavior))
{
	assert(m_quackBehavior);
	SetFlyBehavior(move(flyBehavior));
}

void Duck::Quack() const
{
	m_quackBehavior->Quack();
}
void Duck::Swim()
{
		cout << "I'm swimming" << endl;
}
void Duck::Fly()
{
	m_flyBehavior->Fly();
}
void Duck::Dance()
{
	if (m_danceBehavior)
	{
		m_danceBehavior->Dance();
	}
}
void Duck::SetFlyBehavior(IFlyBehaviorPtr&& flyBehavior)
{
	assert(flyBehavior);
	m_flyBehavior = move(flyBehavior);
}

void Duck::SetDanceBehavior(IDanceBehaviorPtr&& danceBehavior)
{
	m_danceBehavior = move(danceBehavior);
}

MallardDuck::MallardDuck()
	: Duck(make_unique<FlyWithWings>(), make_unique<QuackBehavior>(), make_unique<WaltzDance>())
{
}

void MallardDuck::Display() const
{
	cout << "I'm mallard duck" << endl;
}

RedheadDuck::RedheadDuck()
	: Duck(make_unique<FlyWithWings>(), make_unique<QuackBehavior>(), make_unique<MinuetDance>())
{
}
void RedheadDuck::Display() const
{
	cout << "I'm redhead duck" << endl;
}

DeckoyDuck::DeckoyDuck()
	: Duck(make_unique<FlyNoWay>(), make_unique<MuteQuackBehavior>(), make_unique<NoDance>())
{
}
void DeckoyDuck::Display() const
{
	cout << "I'm deckoy duck" << endl;
}

RubberDuck::RubberDuck()
	: Duck(make_unique<FlyNoWay>(), make_unique<SqueakBehavior>())
{
}

void RubberDuck::Display() const
{
	cout << "I'm rubber duck" << endl;
}

ModelDuck::ModelDuck()
	: Duck(make_unique<FlyNoWay>(), make_unique<QuackBehavior>())
{
}

void ModelDuck::Display() const
{
	cout << "I'm model duck" << endl;
}
