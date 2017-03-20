#pragma once
#include "CColor.h"
#include "ICanvas.h"

class CShape
{
public:
	CShape();
	virtual ~CShape();
	virtual void Draw(ICanvas& canvas) const = 0;
	virtual CColor GetColor() const = 0;
};

