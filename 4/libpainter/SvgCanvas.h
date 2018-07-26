#pragma once
#include "ICanvas.h"

class CSvgCanvas : public ICanvas
{
public:
	CSvgCanvas(std::ostream& out);
	~CSvgCanvas() override;

	void SetPenColor(Color color) override;
	void DrawLine(const PointF& p1, const PointF& p2) override;
	void DrawEllipse(const PointF& center, float rx, float ry) override;

private:
	void PrintStyle();
	std::string ConvertColorToStr(Color c);

	Color m_penColor;
	std::ostream& m_out;
};