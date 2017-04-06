#include "stdafx.h"
#include "ModernGraphiscsClassAdapter.h"

ModernGraphiscsClassAdapter::ModernGraphiscsClassAdapter(std::ostream& output)
	:modern_graphics_lib::CModernGraphicsRenderer(output),
	m_lineBegin(0,0)
{
}

void ModernGraphiscsClassAdapter::BeginDraw()
{
	modern_graphics_lib::CModernGraphicsRenderer::BeginDraw();
}

void ModernGraphiscsClassAdapter::EndDraw()
{
	modern_graphics_lib::CModernGraphicsRenderer::EndDraw();
}

void ModernGraphiscsClassAdapter::MoveTo(int x, int y)
{
	m_lineBegin = { x,y };
}

void ModernGraphiscsClassAdapter::LineTo(int x, int y)
{
	modern_graphics_lib::CModernGraphicsRenderer::DrawLine(m_lineBegin, { x,y });
}
