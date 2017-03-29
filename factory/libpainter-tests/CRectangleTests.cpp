#include "stdafx.h"
#include <sstream>
#include "../libpainter/CRectangle.h"
#include "../libpainter/OStreamCanvas.h"

using namespace std;

struct rectangleFixture
{
	rectangleFixture()
		:leftTop({ 0,1 }),
		rightBottom({ 2,0 }),
		strm(),
		canvas(strm),
		color(Color::Pink),
		rectangle(Color::Pink, { 0,1 }, { 2,0 })
	{}

	CRectangle rectangle;
	Point leftTop;
	Point rightBottom;
	ostringstream strm;
	OStreamCanvas canvas;
	Color color;
};
BOOST_FIXTURE_TEST_SUITE(Rectangle_class, rectangleFixture)
	BOOST_AUTO_TEST_CASE(can_be_drawn)
	{
		stringstream expectedOutput;
		OStreamCanvas tempCanvas(expectedOutput);
		tempCanvas.DrawLine(color, leftTop, { rightBottom.x, leftTop.y });
		tempCanvas.DrawLine(color, { rightBottom.x, leftTop.y }, rightBottom);
		tempCanvas.DrawLine(color, leftTop, { leftTop.x, rightBottom.y });
		tempCanvas.DrawLine(color, { leftTop.x, rightBottom.y }, rightBottom);
		rectangle.Draw(canvas);

		BOOST_CHECK_EQUAL(strm.str(), expectedOutput.str());
	}
	BOOST_AUTO_TEST_CASE(can_get_left_top)
	{
		BOOST_CHECK(rectangle.GetLeftTop() == leftTop);
	}
	BOOST_AUTO_TEST_CASE(can_get_right_bottom)
	{
		BOOST_CHECK(rectangle.GetRightBottom() == rightBottom);
	}
BOOST_AUTO_TEST_SUITE_END()