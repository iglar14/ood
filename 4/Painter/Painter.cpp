// Painter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/Painter.h"
#include "../libpainter/ShapeFactory.h"
#include "../libpainter/SvgCanvas.h"

using namespace std;

void ClientWork(IDesigner& designer, IPainter& painter)
{
	CPictureDraft draft = designer.CreateDraft(cin);
	CSvgCanvas canvas(cout);
	painter.DrawPicture(draft, canvas);
}

int main()
{
	ShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);
	CPainter painter;
	ClientWork(designer, painter);
	
	return 0;
}

