#pragma once
#include "stdafx.h"
#include "CWindDirection.h"

class Stats
{
public:
	double GetMin()
	{
		return m_min;
	}
	double GetMax()
	{
		return m_max;
	}
	double GetAverage()
	{
		return m_average;
	}
	void Update(const double& value)
	{
		if (m_min > value)
		{
			m_min = value;
		}
		if (m_max < value)
		{
			m_max = value;
		}
		m_acc += value;
		++m_countAcc;
		m_average = m_acc / m_countAcc;
	}
	void Update(const WindDirection& direction)
	{
		if (m_directionMin >= direction)
		{
			m_directionMin = direction;
			m_min = m_directionMin;
		}
		if (m_directionMax <= direction)
		{
			m_directionMax = direction;
			m_max = m_directionMax;
		}
		m_directionAcc = m_directionAcc + direction;
		++m_countAcc;
		m_average = m_directionAcc / m_countAcc;
	}
	void Print()
	{
		std::cout << "	max : " << m_max << std::endl;
		std::cout << "	min : " << m_min << std::endl;
		std::cout << "	average : " << m_average << std::endl;
	}
private:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	unsigned int m_directionMin = 360;
	unsigned int m_directionMax = 0;
	WindDirection m_directionAcc = 0;
	double m_average = 0;
	double m_acc = 0;
	unsigned m_countAcc = 0;
};
