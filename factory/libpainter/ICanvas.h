#pragma once
#include "CColor.h"
#include "Point.h"

class ICanvas
{
public:
	ICanvas() {};
	virtual ~ICanvas() {};
	virtual void SetColor(CColor color) = 0;
	virtual void DrawLine(CColor color, Point from, Point to) = 0;
	virtual void DrawEllipse(CColor color, Point center, unsigned wRadius, unsigned hRadius) = 0;
};