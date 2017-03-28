#include "stdafx.h"
#include <sstream>
#include "../libpainter/CPainter.h"
#include "../libpainter/OStreamCanvas.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/Shapes.h"

using namespace std;

struct painterFixture
{
	painterFixture()
		:
		painter(),
		picture(),
		out(),
		canvas(out)
	{}

	CPainter painter;
	CPictureDraft picture;
	OStreamCanvas canvas;
	ostringstream out;
};
BOOST_FIXTURE_TEST_SUITE(CPainter_class, painterFixture)
	BOOST_AUTO_TEST_CASE(should_not_change_canvas_if_picture_is_empty)
	{
		painter.DrawPicture(picture, canvas);
		BOOST_CHECK(out.str().empty());
	}
	BOOST_AUTO_TEST_CASE(can_draw_picture_with_several_shapes)
	{
		ostringstream expectedOut;
		OStreamCanvas testCanvas(expectedOut);
		CTriangle triangle(Color::Pink, { 0,0 }, { 1,1 }, { 2,2 });
		CRectangle rectangle(Color::Pink, { 0,1 }, { 2,0 });
		CRegularPolygon polygon(Color::Pink, { 0,0 }, 6, 3);

		picture.AddShape(make_unique<CTriangle>(triangle));
		picture.AddShape(make_unique<CRectangle>(rectangle));
		picture.AddShape(make_unique<CRegularPolygon>(polygon));
		painter.DrawPicture(picture, canvas);

		triangle.Draw(testCanvas);
		rectangle.Draw(testCanvas);
		polygon.Draw(testCanvas);
		BOOST_CHECK_EQUAL(expectedOut.str(), out.str() );
	}

BOOST_AUTO_TEST_SUITE_END()