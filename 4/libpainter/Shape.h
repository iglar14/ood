#pragma once
#include "Color.h"

class ICanvas;

class CShape
{
public:
	CShape(Color color);
	virtual ~CShape();

	virtual void Draw(ICanvas& canvas);

	virtual Color GetColor() final
	{
		return m_color;
	}

private:
	Color m_color;
};

