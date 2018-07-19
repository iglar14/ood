#pragma once
#include "Point.h"
#include "Shape.h"

class CEllipse : public CShape
{
public:
	CEllipse(Color color, const PointI& center, int hRadius, int vRadius);
	void Draw(ICanvas& canvas) override;

	PointI GetCenter() const { return m_center; }
	int GetHorizontalRadius() const { return m_horizontalRadius; }
	int GetVerticalRadius() const { return m_verticalRadius; }

private:
	PointI m_center;
	int m_horizontalRadius;
	int m_verticalRadius;
};