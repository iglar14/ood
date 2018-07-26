#include "stdafx.h"
#include "SvgCanvas.h"

CSvgCanvas::CSvgCanvas(std::ostream& out)
	: m_out(out)
{
	out << "<svg>\n";
}

CSvgCanvas::~CSvgCanvas()
{
	try
	{
		m_out << "</svg>\n";
	}
	catch (...)
	{
	}
}

void CSvgCanvas::SetPenColor(Color color)
{
	m_penColor = color;
}

void CSvgCanvas::DrawLine(const PointF& p1, const PointF& p2)
{
	m_out << "<line x1=\"" << p1.x << "\" y1=\"" << p1.y << "\" x2=\"" << p2.x << "\" y2=\"" << p2.y << "\" ";
	PrintStyle();
	m_out << " />\n";
}

void CSvgCanvas::DrawEllipse(const PointF& center, float rx, float ry)
{
	m_out << "<ellipse cx=\"" << center.x << "\" cy=\"" << center.y << "\" rx=\"" << rx << "\" ry=\"" << ry << "\" ";
	PrintStyle();
	m_out << " />\n";
}

void CSvgCanvas::PrintStyle()
{
	m_out << "style=\"stroke:";
	m_out << ConvertColorToStr(m_penColor);
	m_out << ";stroke-width:1\"";
}

std::string CSvgCanvas::ConvertColorToStr(Color c)
{
	switch (c)
	{
	case Color::Red:
		return "red";
	case Color::Green:
		return "green";
	case Color::Blue:
		return "blue";
	case Color::Pink:
		return "pink";
	case Color::Yellow:
		return "yellow";
	case Color::Black:
		return "black";
	default:
		return "white";
	}
}
