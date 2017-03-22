#pragma once
#include <memory>
#include <string>
#include <map>
#include <functional>
#include "Shape.h"

struct CShapeFactory
{
	CShapeFactory();
	~CShapeFactory() = default;
	std::unique_ptr<CShape> CreateShape(const std::string & description);
private:
	std::unique_ptr<CShape> CreateTriangle(std::istream & input);
	std::unique_ptr<CShape> CreateRectangle(std::istream & input);
	std::unique_ptr<CShape> CreatePolygon(std::istream & input);
	std::unique_ptr<CShape> CreateEllipse(std::istream & input);

	typedef std::map<std::string, std::function<std::unique_ptr<CShape>(std::istream & args)>> ActionMap;
	const ActionMap m_actionMap;
};

std::istream & operator >> (std::istream & istream, Color & color);