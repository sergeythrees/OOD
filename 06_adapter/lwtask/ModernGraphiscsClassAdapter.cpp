#include "stdafx.h"
#include "ModernGraphiscsClassAdapter.h"

ModernGraphiscsClassAdapter::ModernGraphiscsClassAdapter(std::ostream& output)
	:CModernGraphicsRenderer(output),
	m_lineBegin(0,0)
{
}

void ModernGraphiscsClassAdapter::MoveTo(int x, int y)
{
	m_lineBegin = { x,y };
}

void ModernGraphiscsClassAdapter::LineTo(int x, int y)
{
	DrawLine(m_lineBegin, { x,y });
	m_lineBegin = { x,y };
}
