#include "stdafx.h"
#include "ModernGraphiscsObjectAdapter.h"

ModernGraphiscsObjectAdapter::ModernGraphiscsObjectAdapter(modern_graphics_lib::CModernGraphicsRenderer & renderer)
	:m_renderer(renderer),
	m_lineBegin(0,0)
{
}

void ModernGraphiscsObjectAdapter::MoveTo(int x, int y)
{
	m_lineBegin = modern_graphics_lib::CPoint(x, y);
}

void ModernGraphiscsObjectAdapter::LineTo(int x, int y)
{
	m_renderer.DrawLine(m_lineBegin, modern_graphics_lib::CPoint(x, y));
}
