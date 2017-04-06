#include "stdafx.h"
#include "modern_graphics_lib.h"
#include <boost/format.hpp>

using namespace std;

modern_graphics_lib::CModernGraphicsRenderer::CModernGraphicsRenderer(std::ostream & strm)
	: m_out(strm)
{
}

modern_graphics_lib::CModernGraphicsRenderer::~CModernGraphicsRenderer()
{
	if (m_drawing) // «авершаем рисование, если оно было начато
	{
		EndDraw();
	}
}

void modern_graphics_lib::CModernGraphicsRenderer::BeginDraw()
{
	if (m_drawing)
	{
		throw logic_error("Drawing has already begun");
	}
	m_out << "<draw>" << endl;
	m_drawing = true;
}

void modern_graphics_lib::CModernGraphicsRenderer::DrawLine(const CPoint & start, const CPoint & end)
{
	if (!m_drawing)
	{
		throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
	}
	m_out << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%"/>)")
		% start.x % start.y % end.x % end.y << endl;
}

void modern_graphics_lib::CModernGraphicsRenderer::EndDraw()
{
	if (!m_drawing)
	{
		throw logic_error("Drawing has not been started");
	}
	m_out << "</draw>" << endl;
	m_drawing = false;
}
