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
	float r = ((rgbColor >> 16) & 0x0000FF) / 255.f;
	float g = ((rgbColor >> 8) & 0x0000FF) / 255.f;
	float b = (rgbColor & 0x0000FF) / 255.f;

	m_color = { r, g, b, 1.f };
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