#include "stdafx.h"
#include <sstream>
#include "../libpainter/CRegularPolygon.h"
#include "../libpainter/OStreamCanvas.h"

using namespace std;

namespace
{
	void CheckVerticesVectorEquality(const vector<Point>& a, const vector<Point>& b)
	{
		BOOST_REQUIRE_EQUAL(a.size(), b.size());
		auto size = a.size();
		for (unsigned i = 0; i < size; ++i)
		{
			BOOST_CHECK_CLOSE(a[i].x, b[i].x, 0.1);
			BOOST_CHECK_CLOSE(a[i].y, b[i].y, 0.1);
		}
	}

	template <typename Ex, typename Fn>
	void VerifyException(Fn && fn, const string & expectedDescription)
	{
		BOOST_CHECK_EXCEPTION(fn(), Ex, [&](const Ex& e) {
			BOOST_CHECK_EQUAL(e.what(), expectedDescription);
			return e.what() == expectedDescription;
		});
	}
}

struct polygonFixture
{
	polygonFixture()
		:center({ 0,0 }),
		radius(6),
		verticesCount(3),
		strm(),
		canvas(strm),
		color(Color::Pink),
		polygon(Color::Pink, { 0,0 }, 6, 3)
	{}

	CRegularPolygon polygon;
	Point center;
	unsigned radius;
	unsigned verticesCount;
	OStreamCanvas canvas;
	Color color;
	ostringstream strm;
};
BOOST_FIXTURE_TEST_SUITE(RegularPolygon_class, polygonFixture)
	BOOST_AUTO_TEST_SUITE(CalculatePolygonVertices_function)
		BOOST_AUTO_TEST_CASE(can_calculate_anything_polygon_vertices)
		{
			vector<Point> expectedVertices({ { 6,0 }, { -3,5.2 }, { -3,-5.2 } });
			auto result(CRegularPolygon::CalculatePolygonVertices({ 0,0 }, 6, 3));
			CheckVerticesVectorEquality(expectedVertices, result);
		}
		BOOST_AUTO_TEST_CASE(should_throw_appropriate_exception_if_radius_is_not_positive)
		{
			VerifyException<invalid_argument>([]() {
				CRegularPolygon::CalculatePolygonVertices({ 0,0 }, 0, 3); }, 
				"Radius must have a positive value");
		}
		BOOST_AUTO_TEST_CASE(should_throw_appropriate_exception_if_vertices_count_is_less_than_three)
		{
			VerifyException<invalid_argument>([]() {
				CRegularPolygon::CalculatePolygonVertices({ 0,0 }, 1, 2); }, 
				"Regular polygon must have at least 3 vertices");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_CASE(can_be_drawn)
	{
		stringstream expectedOutput;
		OStreamCanvas tempCanvas(expectedOutput);
		vector<Point> vertices(
			CRegularPolygon::CalculatePolygonVertices({ 0,0 }, 6, 3));

		for (unsigned i = 0; i < verticesCount - 1; ++i)
			tempCanvas.DrawLine(color, vertices[i], vertices[i + 1]);
		tempCanvas.DrawLine(color, vertices[0], vertices[verticesCount - 1]);

		polygon.Draw(canvas);

		BOOST_CHECK_EQUAL(strm.str(), expectedOutput.str());
	}
	BOOST_AUTO_TEST_CASE(can_get_center)
	{
		BOOST_CHECK(polygon.GetCenter() == center);
	}
	BOOST_AUTO_TEST_CASE(can_get_horizontal_radius)
	{
		BOOST_CHECK(polygon.GetRadius() == radius);
	}
	BOOST_AUTO_TEST_CASE(can_get_vertices_count)
	{
		BOOST_CHECK(polygon.GetVerticesCount() == verticesCount);
	}
BOOST_AUTO_TEST_SUITE_END()