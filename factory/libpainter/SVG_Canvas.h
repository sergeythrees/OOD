#pragma once
#include "ICanvas.h"
#include <fstream>

class SVG_Canvas : public ICanvas
{
public:
	SVG_Canvas(const std::string& filePath, Color color = Color::White)
		:m_output(filePath.c_str()),
		m_color(color),
		m_headerWasWritten(false)
	{
	}
	~SVG_Canvas()
	{
		if (m_headerWasWritten)
			WriteEndOfSVG();
	}
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
		if (!m_headerWasWritten)
			WriteHeader();

		m_output << "<line x1=\"" << from.x << "\" y1=\"" << from.y << 
			"\" x2=\"" << to.x << "\" y2=\"" << to.y << "\" stroke-width=\"1\" stroke=\"" 
			<< ColorToHex(color) << "\"/> " << std::endl;
	}
	void DrawEllipse(Color color, Point center, unsigned wRadius, unsigned hRadius) override
	{
		if (!m_headerWasWritten)
			WriteHeader();

		m_output << "<ellipse cx=\"" << center.x << "\" cy=\"" << center.y 
			<< "\" rx=\"" << wRadius << "\" ry=\"" << hRadius 
			<< "\" fill=\"none\" stroke-width=\"1\" stroke=\"" 
			<< ColorToHex(color) << "\"/>" << std::endl;
	}
private:
	std::ofstream m_output;
	bool m_headerWasWritten;
	Color m_color;

	void WriteHeader()
	{
		m_output << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << std::endl
			<< "<rect width = \"100%\" height = \"100%\" fill = \" "<<ColorToHex(m_color) << "\"/>" << std::endl;
		m_headerWasWritten = true;
	}
	void WriteEndOfSVG()
	{
		m_output << "</svg>" << std::endl;
	}
};