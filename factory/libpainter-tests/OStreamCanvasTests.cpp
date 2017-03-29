#include "stdafx.h"
#include <sstream>
#include "../libpainter/OStreamCanvas.h"

using namespace std;
struct canvasFixture
{
	canvasFixture()
		:canvas(OStreamCanvas(strm)) {}
	
	ostringstream strm;
	OStreamCanvas canvas;
};
BOOST_FIXTURE_TEST_SUITE(OStreamCanvas_class, canvasFixture)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(have_white_color)
		{
			BOOST_CHECK(canvas.GetColor() == Color::White);
		}
	BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_CASE(can_set_color)
		{
			canvas.SetColor(Color::Blue);
			BOOST_CHECK(canvas.GetColor() == Color::Blue);
		}
		BOOST_AUTO_TEST_CASE(can_draw_line)
		{
			Color expectedColor = Color::Pink;
			vector<Point> expectedPoints({ { 0,0 },  { 1,1 } });
			stringstream expectedStream;
			expectedStream << "line " << ToString(expectedColor) << " " << expectedPoints[0].x << " " << expectedPoints[0].y
				<< " " << expectedPoints[1].x << " " << expectedPoints[1].y << endl;

			canvas.DrawLine(expectedColor, expectedPoints[0], expectedPoints[1]);

			BOOST_CHECK(strm.str() == expectedStream.str());
		}
		BOOST_AUTO_TEST_CASE(can_draw_ellipse)
		{
			Color expectedColor = Color::Pink;
			Point expectedCenter( 1,1 );
			unsigned expectedHRadius = 2;
			unsigned expectedWRadius = 4;
			stringstream expectedStream;
			expectedStream << "ellipse " << ToString(expectedColor) << " " << expectedCenter.x << " " << expectedCenter.y
				<< " " << expectedWRadius << " " << expectedHRadius << endl;

			canvas.DrawEllipse(expectedColor, expectedCenter, expectedWRadius, expectedHRadius);

			BOOST_CHECK(strm.str() == expectedStream.str());
		}
BOOST_AUTO_TEST_SUITE_END()