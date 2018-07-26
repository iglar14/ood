#pragma once
#include "Color.h"

class ICanvas;

class CShape
{
public:
	CShape(Color color);
	virtual ~CShape();

	virtual void Draw(ICanvas& canvas) = 0;

	virtual Color GetColor() final
	{
		return m_color;
	}
protected:
	void SelectColor(ICanvas& canvas);
private:
	Color m_color;
};

