#pragma once
#include "Point.h"
#include "Shape.h"

class CRegularPolygon : public CShape
{
public:
	class InvalidVertexCount : public std::exception
	{
	public:
		InvalidVertexCount()
			: std::exception("polygon vertex count must be >= 3")
		{}
	};

	CRegularPolygon(Color color, const PointI& center, int radius, unsigned int vertexCount);
	void Draw(ICanvas& canvas) const override;

	PointI GetCenter() const { return m_center; }
	int GetRadius() const { return m_radius; }
	unsigned int GetVertexCount() const { return m_vertexCount; }

private:
	std::vector<PointF> GetVertices() const;

	PointI m_center;
	int m_radius;
	unsigned int m_vertexCount;
};