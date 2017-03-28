#pragma once
#include "ICanvas.h"
#include <iostream>

class OStreamCanvas : public ICanvas
{
public:
	OStreamCanvas(std::ostream& output = std::cout, Color color = Color::White)
		:m_output(output),
		m_color(color)
	{}
	~OStreamCanvas() = default;
	void SetColor(Color color) override
	{
		m_color = color;
	}
	Color GetColor() const override
	{
		return m_color;
	}
	void DrawLine(Color color, Point from, Point to) override
	{
		m_output << "line " << ToString(color) << " " << from.x << " " << from.y 
			<< " " << to.x << " " << to.y << std::endl;
	}
	void DrawEllipse(Color color, Point center, unsigned wRadius, unsigned hRadius) override
	{
		m_output << "ellipse " << ToString(color) << " " << center.x << " " << center.y
			<< " " << wRadius << " " << hRadius << std::endl;
	}
private:
	std::ostream& m_output;
	Color m_color;
};