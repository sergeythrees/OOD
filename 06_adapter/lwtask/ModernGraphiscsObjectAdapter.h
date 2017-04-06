#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib.h"

class ModernGraphiscsObjectAdapter : public graphics_lib::ICanvas
{
public:
	ModernGraphiscsObjectAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer);
	void MoveTo(int x, int y) override;
	void LineTo(int x, int y) override;
private:
	modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
	modern_graphics_lib::CPoint m_lineBegin;
};