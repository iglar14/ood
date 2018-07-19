#pragma once
#include "Point.h"
#include "Shape.h"

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(Color color, const PointI& center, int radius, unsigned int vertexCount);
	void Draw(ICanvas& canvas) override;

	PointI GetCenter() const { return m_center; }
	int GetRadius() const { return m_radius; }
	unsigned int GetVertexCount() const { return m_vertexCount; }

private:
	PointI m_center;
	int m_radius;
	unsigned int m_vertexCount;
};