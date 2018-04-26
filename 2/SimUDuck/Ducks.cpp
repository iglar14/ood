#include <cassert>
#include <iostream>
#include <memory>
#include "Ducks.h"

using namespace std;

void DoNothing() {}

Duck::Duck(FlyBehavior&& flyBehavior,
		QuackBehavior&& quackBehavior,
		DanceBehavior&& danceBehavior)
		: m_quackBehavior(move(quackBehavior))
		, m_danceBehavior(move(danceBehavior))
{
	assert(m_quackBehavior);
	SetFlyBehavior(move(flyBehavior));
}

void Duck::Quack() const
{
	m_quackBehavior();
}
void Duck::Swim()
{
	cout << "I'm swimming" << endl;
}
void Duck::Fly()
{
	m_flyBehavior();
}
void Duck::Dance()
{
	if (m_danceBehavior)
	{
		m_danceBehavior();
	}
}
void Duck::SetFlyBehavior(FlyBehavior&& flyBehavior)
{
	assert(flyBehavior);
	m_flyBehavior = move(flyBehavior);
}

void Duck::SetDanceBehavior(DanceBehavior&& danceBehavior)
{
	m_danceBehavior = move(danceBehavior);
}

MallardDuck::MallardDuck()
	: Duck(FlyWithWings(), &QuackQuack, &WaltzDance)
{
}

void MallardDuck::Display() const
{
	cout << "I'm mallard duck" << endl;
}

RedheadDuck::RedheadDuck()
	: Duck(FlyWithWings(), &QuackQuack, &MinuetDance)
{
}
void RedheadDuck::Display() const
{
	cout << "I'm redhead duck" << endl;
}

DeckoyDuck::DeckoyDuck()
	: Duck(&DoNothing, &DoNothing, &DoNothing)
{
}
void DeckoyDuck::Display() const
{
	cout << "I'm deckoy duck" << endl;
}

RubberDuck::RubberDuck()
	: Duck(&DoNothing, &QuackSqueak)
{
}

void RubberDuck::Display() const
{
	cout << "I'm rubber duck" << endl;
}

ModelDuck::ModelDuck()
	: Duck(&DoNothing, &QuackQuack)
{
}

void ModelDuck::Display() const
{
	cout << "I'm model duck" << endl;
}
