#include "shape_drawing_lib.h"
namespace shape_drawing_lib
{
	CTriangle::CTriangle(const Point & p1, const Point & p2, const Point & p3)
		:m_vertices({ p1, p2, p3 })
	{
	}

	void CTriangle::Draw(graphics_lib::ICanvas & canvas) const
	{
		canvas.MoveTo(m_vertices[0].x, m_vertices[0].y);
		canvas.LineTo(m_vertices[1].x, m_vertices[1].y);

		canvas.MoveTo(m_vertices[1].x, m_vertices[1].y);
		canvas.LineTo(m_vertices[2].x, m_vertices[2].y);

		canvas.MoveTo(m_vertices[2].x, m_vertices[2].y);
		canvas.LineTo(m_vertices[0].x, m_vertices[0].y);
	}

	CRectangle::CRectangle(const Point & leftTop, int width, int height)
		:m_leftTop(leftTop),
		m_width(width), m_height(height)
	{
	}

	void CRectangle::Draw(graphics_lib::ICanvas & canvas) const
	{
		canvas.MoveTo(m_leftTop.x, m_leftTop.y);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);

		canvas.MoveTo(m_leftTop.x + m_width, m_leftTop.y);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y - m_height);

		canvas.MoveTo(m_leftTop.x + m_width, m_leftTop.y - m_height);
		canvas.LineTo(m_leftTop.x, m_leftTop.y - m_height);

		canvas.MoveTo(m_leftTop.x, m_leftTop.y - m_height);
		canvas.LineTo(m_leftTop.x, m_leftTop.y);
	}

	CCanvasPainter::CCanvasPainter(graphics_lib::ICanvas & canvas)
		:m_canvas(canvas)
	{
	}

	void CCanvasPainter::Draw(const ICanvasDrawable & drawable)
	{
		drawable.Draw(m_canvas);
	}
}