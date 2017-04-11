#include "stdafx.h"
#include <iostream>
#include "graphics_lib_pro.h"
#include <boost\format.hpp>
#include <stdint.h>

using namespace std;
namespace graphics_lib_pro
{
	void CCanvas::SetColor(uint32_t rgbColor)
	{
		cout << "SetColor (#" << hex << rgbColor << ")" << endl;
	}

	void CCanvas::MoveTo(int x, int y)
	{
		cout << "MoveTo (" << x << ", " << y << ")" << endl;
	}

	void CCanvas::LineTo(int x, int y)

	{
		cout << "LineTo (" << x << ", " << y << ")" << endl;
	}
}
