#include "graphics_lib.h"
#include <iostream>

using namespace std;

void graphics_lib::CCanvas::MoveTo(int x, int y)
{
	cout << "MoveTo (" << x << ", " << y << ")" << endl;
}

void graphics_lib::CCanvas::LineTo(int x, int y)
{
	cout << "LineTo (" << x << ", " << y << ")" << endl;
}
