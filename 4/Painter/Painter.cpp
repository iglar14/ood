// Painter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/Painter.h"
#include "../libpainter/ShapeFactory.h"
#include "../libpainter/SvgCanvas.h"

using namespace std;

int main()
{
	ShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);
	CPictureDraft draft = designer.CreateDraft(cin);
	CPainter painter;
	CSvgCanvas canvas(cout);
	painter.DrawPicture(draft, canvas);
	
	return 0;
}

