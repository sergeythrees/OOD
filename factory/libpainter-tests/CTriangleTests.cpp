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
		triangle(Color::Pink, { 0,0 }, { 1,1 }, { 2,2 })
	{}

	CTriangle triangle;
	vector<Point> vertices;
	ostringstream strm;
	OStreamCanvas canvas;
	Color color;
};
BOOST_FIXTURE_TEST_SUITE(Triangle_class, triangleFixture)
		BOOST_AUTO_TEST_CASE(can_be_drawn)
		{
			stringstream expectedOutput;
			OStreamCanvas tempCanvas(expectedOutput);
			tempCanvas.DrawLine(color, vertices[0], vertices[1]);
			tempCanvas.DrawLine(color, vertices[1], vertices[2]);
			tempCanvas.DrawLine(color, vertices[0], vertices[2]);
			triangle.Draw(canvas);

			BOOST_CHECK_EQUAL(strm.str(), expectedOutput.str());
		}
		BOOST_AUTO_TEST_CASE(can_get_vertices)
		{
			for (int i = 0; i < vertices.size(); ++i)
			{
				BOOST_CHECK(triangle.GetVertices()[i] == vertices[i]);
			}
		}
BOOST_AUTO_TEST_SUITE_END()