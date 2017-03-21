#include "stdafx.h"
#include <sstream>
#include "../libpainter/CTriangle.h"
#include "../libpainter/OStreamCanvas.h"

using namespace std;

struct triangleFixture
{
	triangleFixture()
		:vertices({ { 0,0 }, { 1,1 }, {2,2} }),
		strm(),
		canvas(strm),
		color(Color::Pink),
		triangle(color, vertices[0], vertices[1], vertices[2])
	{}

	CTriangle triangle;
	vector<Point> vertices;
	OStreamCanvas canvas;
	Color color;
	ostringstream strm;
};
BOOST_FIXTURE_TEST_SUITE(Triangle_class, triangleFixture)
		BOOST_AUTO_TEST_CASE(can_be_drawn)
		{
			stringstream expectedOutput;
			OStreamCanvas tempCanvas;
			tempCanvas.DrawLine(color, vertices[0], vertices[1]);
			tempCanvas.DrawLine(color, vertices[1], vertices[2]);
			tempCanvas.DrawLine(color, vertices[0], vertices[2]);
			triangle.Draw(canvas);

			BOOST_CHECK(strm.str() == expectedOutput.str());
		}
		BOOST_AUTO_TEST_CASE(can_get_vertices)
		{
			BOOST_CHECK(triangle.GetVertices() == vertices);
		}
BOOST_AUTO_TEST_SUITE_END()