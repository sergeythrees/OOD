#pragma once
#include "Point.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CRegularPolygon.h"
#include "CEllipse.h"

namespace {
	bool IsVerticesEqual(const std::vector<Point>& a, const std::vector<Point>& b)
	{
		bool result = true;
		if (a.size() != b.size())
			return false;
		for (size_t i = 0; i < a.size(); ++i)
		{
			if (!(a[i] == b[i]))
				return false;
		}
		return result;
	}

	bool operator == (const CTriangle& a, const CTriangle& b)
	{
		return (a.GetColor() == b.GetColor() && IsVerticesEqual(a.GetVertices(), b.GetVertices()));
	}

	bool operator == (const CRectangle& a, const CRectangle& b)
	{
		return (a.GetColor() == b.GetColor() && 
			a.GetLeftTop()==b.GetLeftTop() && 
			a.GetRightBottom() == b.GetRightBottom() );
	}
	bool operator == (const CRegularPolygon& a, const CRegularPolygon& b)
	{
		return (a.GetColor() == b.GetColor() &&
			a.GetCenter() == b.GetCenter() &&
			a.GetRadius() == b.GetRadius() &&
			a.GetVerticesCount() == b.GetVerticesCount());
	}
	bool operator == (const CEllipse& a, const CEllipse& b)
	{
		return (a.GetColor() == b.GetColor() &&
			a.GetCenter() == b.GetCenter() &&
			a.GetHorizontalRadius() == b.GetHorizontalRadius() &&
			a.GetVerticalRadius() == b.GetVerticalRadius());
	}
}