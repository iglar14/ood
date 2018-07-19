#include "stdafx.h"
#include "Shape.h"
#include "ICanvas.h"

CShape::CShape(Color color)
	: m_color(color)
{
}

CShape::~CShape()
{
}

void CShape::Draw(ICanvas& canvas)
{
	canvas.SetPenColor(m_color);
}
