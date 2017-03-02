#pragma once

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

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino() 
		:CCoffee("Capuccino") 
	{}

	double GetCost() const override 
	{
		return 80; 
	}
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte() 
		:CCoffee("Latte") 
	{}

	double GetCost() const override 
	{
		return 90; 
	}
};

// Чай
enum TeaVariete
{
	Black,
	Oolong,
	Green,
	White
};
std::string ToString(const TeaVariete& variete)
{
	switch (variete)
	{
	case TeaVariete::Oolong:
		return "Oolong Tea";
	case TeaVariete::Black:
		return "Black Tea";
	case TeaVariete::Green:
		return "Green Tea";
	case TeaVariete::White:
		return "White Tea";
	default:
		break;
	}
	return "Tea";

}

class CTea : public CBeverage
{
public:
	CTea(const TeaVariete& teaVariete = TeaVariete::Black) 
		:CBeverage(ToString(teaVariete)) 
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake() 
		:CBeverage("Milkshake") 
	{}

	double GetCost() const override 
	{ 
		return 80; 
	}
};
