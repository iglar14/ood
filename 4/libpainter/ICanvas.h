#pragma once
#include "Color.h"
#include "Point.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void SetPenColor(Color color) = 0;
	virtual void DrawLine(const PointF& p1, const PointF& p2) = 0;
	virtual void DrawEllipse(const PointF& center, float rx, float ry) = 0;
};