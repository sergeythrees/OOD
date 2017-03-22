#include "stdafx.h"
#include "CShapeFactofy.h"
#include <string>
#include <sstream>
#include <iostream>
#include "Shapes.h"
#define CREATE_SHAPE_FUNCTION(function) {\
	[&](std::istream & args) {return this->function(args); }}

using namespace std;
CShapeFactory::CShapeFactory()
	:m_actionMap({
		{ "triangle", CREATE_SHAPE_FUNCTION(CreateTriangle) },
		{ "rectangle", CREATE_SHAPE_FUNCTION(CreateRectangle) },
		{ "polygon", CREATE_SHAPE_FUNCTION(CreatePolygon) },
		{ "ellipse", CREATE_SHAPE_FUNCTION(CreateEllipse) },
})
{
}

std::unique_ptr<CShape> CShapeFactory::CreateShape(const std::string & description)
{
	istringstream strm(description);
	string shapeName;
	strm >> shapeName;
	if (shapeName.empty() ||
		m_actionMap.find(shapeName) == m_actionMap.end())
		throw(invalid_argument("Unknown or empty shape name"));

	return m_actionMap.at(shapeName)(strm);
}

std::unique_ptr<CShape> CShapeFactory::CreateTriangle(std::istream & input)
{
	Point a;
	Point b;
	Point c;
	Color color;
	if (!(input >> color >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y))
		throw invalid_argument("Invalid triangle description");

	return make_unique<CTriangle>(color, a, b, c);
}

std::unique_ptr<CShape> CShapeFactory::CreateRectangle(std::istream & input)
{
	Point a;
	Point b;
	Color color;
	if (!(input >> color >> a.x >> a.y >> b.x >> b.y))
		throw invalid_argument("Invalid rectangle description");

	return make_unique<CRectangle>(color, a, b);
}

std::unique_ptr<CShape> CShapeFactory::CreatePolygon(std::istream & input)
{
	Point c;
	Color color;
	unsigned radius;
	unsigned verticesCount;
	if (!(input >> color >> c.x >> c.y >> radius >> verticesCount))
		throw invalid_argument("Invalid polygon description");

	return make_unique<CRegularPolygon>(color, c, radius, verticesCount);
}

std::unique_ptr<CShape> CShapeFactory::CreateEllipse(std::istream & input)
{
	Point c;
	Color color;
	unsigned wRadius;
	unsigned hRadius;
	if (!(input >> color >> c.x >> c.y >> wRadius >> hRadius))
		throw invalid_argument("Invalid ellipse description");

	return make_unique<CEllipse>(color, c, wRadius, hRadius);
}

istream & operator >> (istream & istream, Color & color) {

	string colorName;
	istream >> colorName;
	color = StringToColor(colorName);
	return istream;
}