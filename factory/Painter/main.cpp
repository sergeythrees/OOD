// Painter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "../libpainter/CPainter.h"
#include "../libpainter/CShapeFactofy.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/SVG_Canvas.h"
#include "../libpainter/Designer.h"

using namespace std;

int main()
{
	ifstream inputFile("input.txt");
	CShapeFactory factory;
	CDesigner designer  = CDesigner(factory);
	CPictureDraft picture(designer.CreateDraft(inputFile));
	SVG_Canvas canvas("out.svg", Color::Black);
	CPainter painter;

	painter.DrawPicture(picture, canvas);

	return 0;
}

