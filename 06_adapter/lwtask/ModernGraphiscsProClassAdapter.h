#pragma once
#include "stdafx.h"
#include "graphics_lib_pro.h"
#include "modern_graphics_lib_pro.h"


class ModernGraphiscsProClassAdapter : 
	public graphics_lib_pro::ICanvas,
	private modern_graphics_lib_pro::CModernGraphicsRenderer
{
public:
	ModernGraphiscsProClassAdapter(std::ostream& output = std::cout);
	void SetColor(uint32_t rgbColor) override;
	using CModernGraphicsRenderer::BeginDraw;
	using CModernGraphicsRenderer::EndDraw;
	void MoveTo(int x, int y) override;
	void LineTo(int x, int y) override;
private:
	modern_graphics_lib_pro::CPoint m_lineBegin;
	modern_graphics_lib_pro::CRGBAColor m_color;
};