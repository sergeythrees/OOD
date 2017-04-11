#include "stdafx.h"
#include "ModernGraphicsObjectAdapter.h"

ModernGraphicsObjectAdapter::ModernGraphicsObjectAdapter(modern_graphics_lib::CModernGraphicsRenderer & renderer)
	:m_renderer(renderer),
	m_lineBegin(0,0)
{
}

void ModernGraphicsObjectAdapter::MoveTo(int x, int y)
{
	m_lineBegin = modern_graphics_lib::CPoint(x, y);
}

void ModernGraphicsObjectAdapter::LineTo(int x, int y)
{
	m_renderer.DrawLine(m_lineBegin, modern_graphics_lib::CPoint(x, y));
	m_lineBegin = { x,y };
}
