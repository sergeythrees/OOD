#pragma once
#include "Color.h"
#include "ICanvas.h"

class CShape
{
public:
	CShape(Color color = Color::Black)
		:m_color(color)
	{}
	virtual ~CShape();
	virtual void Draw(ICanvas& canvas) const = 0;
	Color GetColor() const
	{
		return m_color;
	}
private:
	Color m_color;
};

