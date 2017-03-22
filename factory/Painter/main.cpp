// Painter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "../libpainter/CPainter.h"
#include "../libpainter/CShapeFactofy.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/OStreamCanvas.h"
#include "../libpainter/Designer.h"

using namespace std;

int main()
{
	CShapeFactory factory;
	CDesigner designer  = CDesigner(factory);
	CPictureDraft picture(designer.CreateDraft(cin));
	OStreamCanvas canvas;
	CPainter painter;

	painter.DrawPicture(picture, canvas);

	return 0;
}

