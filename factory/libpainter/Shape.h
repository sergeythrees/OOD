#pragma once
#include "CColor.h"
#include "ICanvas.h"

class CShape
{
public:
	CShape(CColor color = CColor::Black)
		:m_color(color)
	{}
	virtual ~CShape();
	virtual void Draw(ICanvas& canvas) const = 0;
	CColor GetColor() const
	{
		return m_color;
	}
private:
	CColor m_color;
};

