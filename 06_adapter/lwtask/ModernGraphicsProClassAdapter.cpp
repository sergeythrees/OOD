#include "stdafx.h"
#include <string>
#include <sstream>
#include "ModernGraphicsProClassAdapter.h"

using namespace std;

ModernGraphicsProClassAdapter::ModernGraphicsProClassAdapter(std::ostream & output)
	:modern_graphics_lib_pro::CModernGraphicsRenderer(output),
	m_lineBegin(0,0), 
	m_color(00, 00, 00, 00)
{
}

void ModernGraphicsProClassAdapter::SetColor(uint32_t rgbColor)
{
	m_color.r = ((rgbColor >> 16) & 0xFF) / 255.f;
	m_color.g = ((rgbColor >> 8) & 0xFF) / 255.f;
	m_color.b = (rgbColor & 0xFF) / 255.f;
	m_color.a = 1.0;
}

void ModernGraphicsProClassAdapter::MoveTo(int x, int y)
{
	m_lineBegin = { x,y };
}

void ModernGraphicsProClassAdapter::LineTo(int x, int y)
{
	DrawLine(m_lineBegin, { x,y }, m_color);
	m_lineBegin = { x,y };
}