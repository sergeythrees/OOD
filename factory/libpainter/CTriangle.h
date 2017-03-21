#pragma once
#include "Shape.h"
#include "Point.h"
#include <vector>

class CTriangle : public CShape
{
public:
	CTriangle(Color color, Point vertice1, Point vertice2, Point vertice3)
		:CShape(color),
		m_vertices({vertice1, vertice2, vertice3})
	{
	}
	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawLine(GetColor(), m_vertices[0], m_vertices[1]);
		canvas.DrawLine(GetColor(), m_vertices[1], m_vertices[2]);
		canvas.DrawLine(GetColor(), m_vertices[0], m_vertices[2]);
	}
	vector<Point> GetVertices()
	{
		return m_vertices;
	}
private:
	std::vector<Point> m_vertices;
};