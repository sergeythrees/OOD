#pragma once
#include "ICanvas.h"

class CShape
{
public:
	CShape();
	virtual ~CShape();
	virtual void Draw(ICanvas& canvas) const = 0;
	CColor GetColor() const
	{
		return m_color;
	}
private:
	CColor m_color;
};

