#include "stdafx.h"
#include <sstream>
#include "../libpainter/Shapes.h"
#include "../libpainter/CShapeFactofy.h"
#include "../libpainter/OStreamCanvas.h"
#include "VerifyExceptions.h"

using namespace std;

struct factoryFixture
{
	factoryFixture()
		:
		factory(),
		out(),
		canvas(out)
	{}

	CShapeFactory factory;
	OStreamCanvas canvas;
	ostringstream out;
};
BOOST_FIXTURE_TEST_SUITE(CShapeFactory_class, factoryFixture)
	BOOST_AUTO_TEST_CASE(can_create_triangle)
	{
		CTriangle triangle(Color::Pink, { 0,0 }, { 1,1 }, { 2,2 });
		auto shapePtr = factory.CreateShape("triangle pink 0 0 1 1 2 2");
		BOOST_CHECK(triangle == *dynamic_cast<CTriangle *>(shapePtr.get()));
	}
	BOOST_AUTO_TEST_CASE(can_create_rectangle)
	{
		CRectangle rectangle(Color::Pink, { 0,1 }, { 2,0 });
		auto shapePtr = factory.CreateShape("rectangle pink 0 1 2 0");
		BOOST_CHECK(rectangle == *dynamic_cast<CRectangle *>(shapePtr.get()));
	}
	BOOST_AUTO_TEST_CASE(can_create_regular_polygon)
	{
		CRegularPolygon polygon(Color::Pink, { 0,0 }, 6, 3);
		auto shapePtr = factory.CreateShape("polygon pink 0 0 6 3");
		BOOST_CHECK(polygon == *dynamic_cast<CRegularPolygon *>(shapePtr.get()));
	}
	BOOST_AUTO_TEST_CASE(can_create_ellipse)
	{
		CEllipse ellipse(Color::Pink, { 0,1 }, 6, 3);
		auto shapePtr = factory.CreateShape("ellipse pink 0 1 6 3");
		BOOST_CHECK(ellipse == *dynamic_cast<CEllipse *>(shapePtr.get()));
	}
	BOOST_AUTO_TEST_CASE(is_case_insensitive)
	{
		CEllipse ellipse(Color::Pink, { 0,1 }, 6, 3);
		auto shapePtr = factory.CreateShape("Ellipse Pink 0 1 6 3");
		BOOST_CHECK(ellipse == *dynamic_cast<CEllipse *>(shapePtr.get()));
	}
	BOOST_AUTO_TEST_SUITE(should_throw_apptoptiate_exception)
		BOOST_AUTO_TEST_CASE(if_shape_name_in_description_is_incorrect)
		{
			VerifyException<invalid_argument>([&]() {
				factory.CreateShape(""); }, 
				"Unknown or empty shape name");
			VerifyException<invalid_argument>([&]() {
				factory.CreateShape("unknown"); },
				"Unknown or empty shape name");
		}
		BOOST_AUTO_TEST_CASE(if_shape_description_is_not_valid)
		{
			VerifyException<invalid_argument>([&]() {
				factory.CreateShape("triangle unknownColor 1 0 2 2 3 0"); }, 
				"Unknown color name");
			VerifyException<invalid_argument>([&]() {
				factory.CreateShape("rectangle pink 1 0 2 "); },
				"Invalid rectangle description");
			VerifyException<invalid_argument>([&]() {
				factory.CreateShape("polygon pink 1 0"); },
				"Invalid polygon description");
			VerifyException<invalid_argument>([&]() {
				factory.CreateShape("ellipse pink 1 0 2"); },
				"Invalid ellipse description");
		}
		BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()