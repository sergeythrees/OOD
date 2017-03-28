#pragma once
#include "stdafx.h"

template <typename T>
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
	void Update(const T& value)
	{
		if (m_min > value)
		{
			m_min = value;
		}
		if (m_max < value)
		{
			m_max = value;
		}
		m_acc = m_acc + value;
		++m_countAcc;
		m_average = m_acc / m_countAcc;
	}
	void Print()
	{
		std::cout << "	max : " << m_max << std::endl;
		std::cout << "	min : " << m_min << std::endl;
		std::cout << "	average : " << m_average << std::endl;
	}
private:
	double m_min = std::numeric_limits<double>::infinity();;
	double m_max = -std::numeric_limits<double>::infinity();;
	double m_average = 0;
	T m_acc = 0;
	unsigned m_countAcc = 0;
};
