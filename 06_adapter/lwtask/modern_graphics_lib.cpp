#include "stdafx.h"
#include "modern_graphics_lib.h"
#include <boost/format.hpp>

using namespace std;
namespace modern_graphics_lib
{
	CModernGraphicsRenderer::CModernGraphicsRenderer(std::ostream & strm)
		: m_out(strm)
	{
	}

	CModernGraphicsRenderer::~CModernGraphicsRenderer()
	{
		if (m_drawing) // ��������� ���������, ���� ��� ���� ������
		{
			EndDraw();
		}
	}

	void CModernGraphicsRenderer::BeginDraw()
	{
		if (m_drawing)
		{
			throw logic_error("Drawing has already begun");
		}
		m_out << "<draw>" << endl;
		m_drawing = true;
	}

	void CModernGraphicsRenderer::DrawLine(const CPoint & start, const CPoint & end)
	{
		if (!m_drawing)
		{
			throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
		}
		m_out << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%"/>)")
			% start.x % start.y % end.x % end.y << endl;
	}

	void CModernGraphicsRenderer::EndDraw()
	{
		if (!m_drawing)
		{
			throw logic_error("Drawing has not been started");
		}
		m_out << "</draw>" << endl;
		m_drawing = false;
	}

}
