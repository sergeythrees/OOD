#pragma once
#include <iostream>
#include "graphics_lib.h"
#include "modern_graphics_lib.h"

class ModernGraphicsClassAdapter : 
	public graphics_lib::ICanvas,
	private modern_graphics_lib::CModernGraphicsRenderer
{
public:
	using CModernGraphicsRenderer::BeginDraw;
	using CModernGraphicsRenderer::EndDraw;
	ModernGraphicsClassAdapter(std::ostream& output = std::cout);
	void MoveTo(int x, int y) override;
	void LineTo(int x, int y) override;
private:
	modern_graphics_lib::CPoint m_lineBegin;
};