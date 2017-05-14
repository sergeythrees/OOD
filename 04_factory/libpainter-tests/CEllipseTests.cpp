#include "stdafx.h"
#include <sstream>
#include "../libpainter/CEllipse.h"
#include "../libpainter/OStreamCanvas.h"

using namespace std;

struct ellipseFixture
{
	ellipseFixture()
		:center({ 0,1 }),
		wRadius(6),
		hRadius(3),
		strm(),
		canvas(strm),
		color(Color::Pink),
		ellipse(Color::Pink, { 0,1 }, 6, 3)
	{}
	
	Point center;
	unsigned wRadius;
	unsigned hRadius;
	ostringstream strm;
	OStreamCanvas canvas;
	Color color;
	CEllipse ellipse;
};
BOOST_FIXTURE_TEST_SUITE(Ellipse_class, ellipseFixture)
	BOOST_AUTO_TEST_CASE(can_be_drawn)
	{
		stringstream expectedOutput;
		OStreamCanvas tempCanvas(expectedOutput);
		tempCanvas.DrawEllipse(color, center, wRadius, hRadius);
		ellipse.Draw(canvas);

		BOOST_CHECK_EQUAL(strm.str(), expectedOutput.str());
	}
	BOOST_AUTO_TEST_CASE(can_get_center)
	{
		BOOST_CHECK(ellipse.GetCenter() == center);
	}
	BOOST_AUTO_TEST_CASE(can_get_horizontal_radius)
	{
		BOOST_CHECK(ellipse.GetHorizontalRadius() == wRadius);
	}
	BOOST_AUTO_TEST_CASE(can_get_vertical_radius)
	{
		BOOST_CHECK(ellipse.GetVerticalRadius() == hRadius);
	}
BOOST_AUTO_TEST_SUITE_END()