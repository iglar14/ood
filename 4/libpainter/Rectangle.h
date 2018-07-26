#pragma once
#include "Point.h"
#include "Shape.h"

class CRectangle : public CShape
{
public:
	CRectangle(Color color, const PointI& leftTop, const PointI& rightBottom);
	void Draw(ICanvas& canvas) const override;

	PointI GetLeftTop() const { return m_leftTop; }
	PointI GetRightBottom() const { return m_rightBottom; }

private:
	PointI m_leftTop;
	PointI m_rightBottom;
};
