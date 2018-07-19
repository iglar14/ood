#include "stdafx.h"
#include "RegularPolygon.h"

CRegularPolygon::CRegularPolygon(Color color, const PointI& center, int radius, unsigned int vertexCount)
	: CShape(color)
	, m_center(center)
	, m_radius(radius)
	, m_vertexCount(vertexCount)
{
}

void CRegularPolygon::Draw(ICanvas& /*canvas*/)
{

}
