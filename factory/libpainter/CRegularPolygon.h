#pragma once
#include "Shape.h"
#include "Point.h"
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(Color color, Point center, unsigned radius, unsigned verticesCount)
		:CShape(color),
		m_center(center),
		m_radius(radius)
	{
		m_vertices = CalculatePolygonVertices(center, radius, verticesCount);
	}
	void Draw(ICanvas& canvas) const override
	{
		for (unsigned i = 0; i < m_vertices.size() - 1; ++i)
			canvas.DrawLine(GetColor(), m_vertices[i], m_vertices[i + 1]);
		canvas.DrawLine(GetColor(), m_vertices[0], m_vertices[m_vertices.size() - 1]);
	}
	Point GetCenter() const
	{
		return m_center;
	}
	unsigned GetVerticesCount() const
	{
		return static_cast<unsigned>(m_vertices.size());
	}
	unsigned GetRadius() const
	{
		return m_radius;
	}
	static std::vector<Point> CalculatePolygonVertices(Point center, unsigned radius, unsigned verticesCount)
	{
		std::vector<Point> vertices;
		if (verticesCount < 3)
			throw std::invalid_argument("Regular polygon must have at least 3 vertices");
		if (radius <= 0)
			throw std::invalid_argument("Radius must have a positive value");

		for (unsigned vertexIndex = 0; vertexIndex < verticesCount; ++vertexIndex)
		{
			double radian = (M_PI * 2.0) / double(verticesCount) * double(vertexIndex);
			vertices.push_back({
				double(radius) * std::cos(radian) + center.x,
				double(radius) * std::sin(radian) + center.y });
		}
		return vertices;
	}
private:
	Point m_center;
	unsigned m_radius;
	std::vector<Point> m_vertices;
};