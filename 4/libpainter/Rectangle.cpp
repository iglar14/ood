#include "stdafx.h"
#include "Rectangle.h"
#include "ICanvas.h"

CRectangle::CRectangle(Color color, const PointI& leftTop, const PointI& rightBottom)
	: CShape(color)
	, m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
{

};

void CRectangle::Draw(ICanvas& canvas)
{
	SelectColor(canvas);

	const PointF leftTop = MakePointF(m_leftTop);
	const PointF rightBottom = MakePointF(m_rightBottom);
	const PointF rightTop{ rightBottom.x, leftTop.y };
	const PointF leftBottom{ leftTop.x, rightBottom.y };

	canvas.DrawLine(leftTop, rightTop);
	canvas.DrawLine(rightTop, rightBottom);
	canvas.DrawLine(rightBottom, leftBottom);
	canvas.DrawLine(leftBottom, leftTop);
}
