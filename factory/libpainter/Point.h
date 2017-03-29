#pragma once
struct Point
{
	Point()
		:x(0), y(0) {}
	Point(double x, double y)
		: x(x), y(y) {}
	double x;
	double y;

	bool operator == (const Point& b) const
	{
		return ((this->x - b.x) < DBL_EPSILON && (this->y - b.y) < DBL_EPSILON);
	}
};