#include "stdafx.h"
#include <string>
#include <sstream>
#include "ModernGraphiscsProClassAdapter.h"

using namespace std;

ModernGraphiscsProClassAdapter::ModernGraphiscsProClassAdapter(std::ostream & output)
	:modern_graphics_lib_pro::CModernGraphicsRenderer(output),
	m_lineBegin(0,0), 
	m_color(00, 00, 00, 00)
{
}

void ModernGraphiscsProClassAdapter::SetColor(uint32_t rgbColor)
{
	ostringstream strm;
	strm << rgbColor;
	string rgbString(strm.str());
	if (rgbString.length() != 6)
		throw invalid_argument("Invalid color value");

	m_color = { stof(rgbString.substr(0,2)),
				stof(rgbString.substr(2,2)),
				stof(rgbString.substr(4,2)), 
				1.0 };
}

void ModernGraphiscsProClassAdapter::MoveTo(int x, int y)
{
	m_lineBegin = { x,y };
}

void ModernGraphiscsProClassAdapter::LineTo(int x, int y)
{
	modern_graphics_lib_pro
		::CModernGraphicsRenderer::DrawLine(
		m_lineBegin, { x,y }, m_color);
}

void ModernGraphiscsProClassAdapter::BeginDraw()
{
	modern_graphics_lib_pro::CModernGraphicsRenderer::BeginDraw();
}

void ModernGraphiscsProClassAdapter::EndDraw()
{
	modern_graphics_lib_pro::CModernGraphicsRenderer::EndDraw();
}
