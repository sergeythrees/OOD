#pragma once
#include "Color.h"
#include "Point.h"

class ICanvas
{
public:
	ICanvas() = default;
	virtual ~ICanvas() = default;
	virtual void SetColor(Color color) = 0;
	virtual Color GetColor() const = 0;
	virtual void DrawLine(Color color, Point from, Point to) = 0;
	virtual void DrawEllipse(Color color, Point center, unsigned wRadius, unsigned hRadius) = 0;
};