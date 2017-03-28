#pragma once
#include "Shape.h"
#include "Point.h"

class CEllipse : public CShape
{
public:
	CEllipse(Color color, Point center, unsigned wRadius, unsigned hRadius)
		:CShape(color),
		m_center(center),
		m_wRadius(wRadius),
		m_hRadius(hRadius)
	{
	}
	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawEllipse(GetColor(), m_center, m_wRadius, m_hRadius);
	}
	Point GetCenter() const
	{
		return m_center;
	}
	unsigned GetHorizontalRadius() const
	{
		return m_wRadius;
	}
	unsigned GetVerticalRadius() const
	{
		return m_hRadius;
	}
private:
	Point m_center;
	unsigned m_wRadius;
	unsigned m_hRadius;
};