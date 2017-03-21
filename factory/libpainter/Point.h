#pragma once
struct Point
{
	Point(double x, double y)
		: x(x), y(y)
	{
	}
	double x = 0;
	double y = 0;

	bool operator == (Point b)
	{
		return (this->x == b.x && this->y == b.y);
	}
};