#include "modern_graphics_lib_pro.h"
#include <boost/format.hpp>

using namespace std;

modern_graphics_lib_pro::CModernGraphicsRenderer::CModernGraphicsRenderer(std::ostream & strm)
	: m_out(strm)
{
}


modern_graphics_lib_pro::CModernGraphicsRenderer::~CModernGraphicsRenderer()
{
	if (m_drawing) // «авершаем рисование, если оно было начато
	{
		EndDraw();
	}
}

void modern_graphics_lib_pro::CModernGraphicsRenderer::BeginDraw()
{
	if (m_drawing)
	{
		throw logic_error("Drawing has already begun");
	}
	m_out << "<draw>" << endl;
	m_drawing = true;
}

void modern_graphics_lib_pro::CModernGraphicsRenderer::DrawLine(const CPoint & start, const CPoint & end, const CRGBAColor & color)
{
	if (!m_drawing)
	{
		throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
	}
	m_out << boost::format(R"(  <line fromX="%1%" fromY="%2" toX="%3%" toY="%4%"/>)") 
		% start.x % start.y % end.x % end.y << endl;
	m_out << boost::format(R"(    <color r="%1$.3f" g="%2$.3f" b="%3$.3f" a="%4$.3f" />)") 
		% color.r % color.g % color.b % color.a << endl;
	m_out << "  </line>" << endl;
}


void modern_graphics_lib_pro::CModernGraphicsRenderer::EndDraw()
{
	if (!m_drawing)
	{
		throw logic_error("Drawing has not been started");
	}
	m_out << "</draw>" << endl;
	m_drawing = false;
}
