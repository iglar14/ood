#pragma once
#include "Point.h"
#include "Shape.h"

class CTriangle : public CShape
{
public:
	CTriangle(Color color, const PointI& v1, const PointI& v2, const PointI& v3);
	void Draw(ICanvas& canvas) const override;

	PointI GetVertex1() const { return m_vertices[0]; }
	PointI GetVertex2() const { return m_vertices[1]; }
	PointI GetVertex3() const { return m_vertices[2]; }

private:
	PointI m_vertices[3];
};