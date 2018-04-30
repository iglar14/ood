#pragma once
#include <assert.h>
#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description) 
	{}

	double GetCost() const override 
	{
		return 60; 
	}
};

enum class CoffeePortion
{
	Single = 1,
	Double = 2,
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(CoffeePortion portion = CoffeePortion::Single)
		:CCoffee((portion == CoffeePortion::Single) ? "Capuccino" : "Double Capuccino")
	{}

	double GetCost() const override 
	{
		return (m_portion == CoffeePortion::Single) ? 80 : 120;
	}
private:
	CoffeePortion m_portion;
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffeePortion portion = CoffeePortion::Single)
		: CCoffee((portion == CoffeePortion::Single) ? "Latte" : "Double Latte")
		, m_portion(portion)
	{}

	double GetCost() const override 
	{
		return (m_portion == CoffeePortion::Single) ? 90 : 130;
	}
private:
	CoffeePortion m_portion;
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(const std::string& name)
		:CBeverage(name + " Tea") 
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};

class CBlackTea : public CTea
{
public:
	CBlackTea() : CTea("Black") {}
};

class CGreenTea : public CTea
{
public:
	CGreenTea() : CTea("Green") {}
};

class CIndianTea : public CTea
{
public:
	CIndianTea() : CTea("Indian") {}
};

class CAhmatTea : public CTea
{
public:
	CAhmatTea() : CTea("Ahmat") {}
};

enum class MilkshakePortion
{
	Small = 1,
	Medium = 2,
	Big = 3,
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakePortion portion = MilkshakePortion::Small)
		: CBeverage(std::string(
				(portion == MilkshakePortion::Small) ? "Small" :
				(portion == MilkshakePortion::Medium) ? "Medium" : "Big")
			+ " Milkshake")
		, m_portion(portion)
	{}

	double GetCost() const override 
	{ 
		switch (m_portion)
		{
		case MilkshakePortion::Small:
			return 50;
		case MilkshakePortion::Medium:
			return 60;
		case MilkshakePortion::Big:
			return 80;
		default:
			assert(false);
			return 80;
		}
	}
private:
	MilkshakePortion m_portion = MilkshakePortion::Small;
};
