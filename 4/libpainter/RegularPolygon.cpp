#include "stdafx.h"
#define _USE_MATH_DEFINES // for C++  
#include <math.h>
#include "ICanvas.h"
#include "RegularPolygon.h"

CRegularPolygon::CRegularPolygon(Color color, const PointI& center, int radius, unsigned int vertexCount)
	: CShape(color)
	, m_center(center)
	, m_radius(radius)
	, m_vertexCount(vertexCount)
{
	if (vertexCount < 3)
	{
		throw InvalidVertexCount();
	}
}

void CRegularPolygon::Draw(ICanvas& canvas)
{
	SelectColor(canvas);

	const auto vertices = GetVertices();
	const size_t vertexCount = vertices.size();
	for (size_t i = 0; i < vertexCount; ++i)
	{
		canvas.DrawLine(vertices[i], vertices[(i + 1) % vertexCount]);
	}
}

std::vector<PointF> CRegularPolygon::GetVertices() const
{
	std::vector<PointF> vertices;
	vertices.reserve(m_vertexCount);
	const PointF center = MakePointF(m_center);
	double i = 0;
	std::generate_n(std::back_inserter(vertices), m_vertexCount, [&] {
		const double vertexAngle = (2 * M_PI * i) / m_vertexCount;
		const float x = static_cast<float>(sin(vertexAngle)) * m_radius;
		const float y = static_cast<float>(cos(vertexAngle)) * m_radius;
		++i;
		return PointF{ center.x + x, center.y + y };
	});
	return vertices;
}
