#include "stdafx.h"
#include "Triangle.h"
#include "ICanvas.h"

CTriangle::CTriangle(Color color, const PointI& v1, const PointI& v2, const PointI& v3)
	: CShape(color)
	, m_vertices{v1, v2, v3}
{}

void CTriangle::Draw(ICanvas& canvas)
{
	CShape::Draw(canvas);

	const PointF v0 = MakePointF(m_vertices[0]);
	const PointF v1 = MakePointF(m_vertices[1]);
	const PointF v2 = MakePointF(m_vertices[2]);
	canvas.DrawLine(v0, v1);
	canvas.DrawLine(v1, v2);
	canvas.DrawLine(v2, v0);
}
