#pragma once
#include "Shape.h"
#include "Point.h"

class CRectangle : public CShape
{
public:
	CRectangle(Color color, Point leftTop, Point rightBottom)
		:CShape(color),
		m_leftTop(leftTop),
		m_rightBottom(rightBottom)
	{
	}
	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawLine(GetColor(), m_leftTop, { m_rightBottom.x, m_leftTop.y });
		canvas.DrawLine(GetColor(), { m_rightBottom.x, m_leftTop.y }, m_rightBottom );
		canvas.DrawLine(GetColor(), m_leftTop, {m_leftTop.x, m_rightBottom.y });
		canvas.DrawLine(GetColor(), { m_leftTop.x, m_rightBottom.y }, m_rightBottom);
	}
	Point GetLeftTop()
	{
		return m_leftTop;
	}
	Point GetRightBottom()
	{
		return m_rightBottom;
	}
private:
	Point m_leftTop; 
	Point m_rightBottom;
};