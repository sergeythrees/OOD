#pragma once
struct Point
{
	Point(int x, int y)
		: x(x), y(y)
	{
	}
	int x = 0;
	int y = 0;

	bool operator == (Point b)
	{
		return (this->x == b.x && this->y == b.y);
	}
};