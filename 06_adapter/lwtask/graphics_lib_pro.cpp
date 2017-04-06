#include "stdafx.h"
#include <iostream>
#include "graphics_lib_pro.h"

using namespace std;

void graphics_lib_pro::CCanvas::SetColor(uint32_t rgbColor)
{
	cout << "SetColor (#" << rgbColor <<")" << endl;
}

void graphics_lib_pro::CCanvas::MoveTo(int x, int y)
{
	cout << "MoveTo (" << x << ", " << y << ")" << endl;
}

void graphics_lib_pro::CCanvas::LineTo(int x, int y)

{
	cout << "LineTo (" << x << ", " << y << ")" << endl;
}
