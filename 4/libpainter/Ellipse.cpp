#include "stdafx.h"
#include "Ellipse.h"
#include "ICanvas.h"

CEllipse::CEllipse(Color color, const PointI& center, int hRadius, int vRadius)
	: CShape(color)
	, m_center(center)
	, m_horizontalRadius(hRadius)
	, m_verticalRadius(vRadius)
{
}

void CEllipse::Draw(ICanvas& canvas)
{
	SelectColor(canvas);
	canvas.DrawEllipse(MakePointF(m_center), static_cast<float>(m_horizontalRadius), static_cast<float>(m_verticalRadius));
}
