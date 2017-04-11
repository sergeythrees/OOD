#include "stdafx.h"
#include "ModernGraphicsClassAdapter.h"

ModernGraphicsClassAdapter::ModernGraphicsClassAdapter(std::ostream& output)
	:CModernGraphicsRenderer(output),
	m_lineBegin(0,0)
{
}

void ModernGraphicsClassAdapter::MoveTo(int x, int y)
{
	m_lineBegin = { x,y };
}

void ModernGraphicsClassAdapter::LineTo(int x, int y)
{
	DrawLine(m_lineBegin, { x,y });
	m_lineBegin = { x,y };
}
