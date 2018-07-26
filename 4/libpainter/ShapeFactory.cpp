#include "stdafx.h"
#include "ShapeFactory.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "RegularPolygon.h"

static PointI GetPoint(boost::smatch xResults, size_t index)
{
	int x = boost::lexical_cast<int>(xResults[index]);
	int y = boost::lexical_cast<int>(xResults[index + 1]);
	return PointI{ x, y };
}
ShapeFactory::ShapeFactory()
{
	m_colorMap["red"] = Color::Red;
	m_colorMap["green"] = Color::Green;
	m_colorMap["blue"] = Color::Blue;
	m_colorMap["pink"] = Color::Pink;
	m_colorMap["yellow"] = Color::Yellow;
	m_colorMap["black"] = Color::Black;
}

ShapeFactory::~ShapeFactory()
{
}

static const char* REGEXP_RECT = "rectangle\\s+(\\w+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)";
static const char* REGEXP_TRIANGLE = "triangle\\s+(\\w+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)";
static const char* REGEXP_ELLIPSE = "ellipse\\s+(\\w+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)\\s+(\\d+)\\s+(\\d+)";
static const char* REGEXP_POLYGON = "polygon\\s+(\\w+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)\\s+(\\d+)\\s+(\\d+)";

CShapeUniquePtr ShapeFactory::CreateShape(const std::string & description)
{
	boost::smatch xResults;
	if (boost::regex_match(description, xResults, boost::regex(REGEXP_RECT)))
	{
		Color color = CreateColor(xResults[1]);
		const PointI lt = GetPoint(xResults, 2);
		const PointI rb = GetPoint(xResults, 4);
		return std::make_unique<CRectangle>(color, lt, rb);
	}
	else if (boost::regex_match(description, xResults, boost::regex(REGEXP_TRIANGLE)))
	{
		Color color = CreateColor(xResults[1]);
		const PointI v1 = GetPoint(xResults, 2);
		const PointI v2 = GetPoint(xResults, 4);
		const PointI v3 = GetPoint(xResults, 6);
		return std::make_unique<CTriangle>(color, v1, v2, v3);
	}
	else if (boost::regex_match(description, xResults, boost::regex(REGEXP_ELLIPSE)))
	{
		Color color = CreateColor(xResults[1]);
		const PointI center = GetPoint(xResults, 2);
		const int rx = boost::lexical_cast<int>(xResults[4]);
		const int ry = boost::lexical_cast<int>(xResults[5]);
		return std::make_unique<CEllipse>(color, center, rx, ry);
	}
	else if (boost::regex_match(description, xResults, boost::regex(REGEXP_POLYGON)))
	{
		Color color = CreateColor(xResults[1]);
		const PointI center = GetPoint(xResults, 2);
		const int radius = boost::lexical_cast<int>(xResults[4]);
		const int count = boost::lexical_cast<int>(xResults[5]);
		return std::make_unique<CRegularPolygon>(color, center, radius, count);
	}
	return nullptr;
}

Color ShapeFactory::CreateColor(const std::string& colorStr) const
{
	auto iter = m_colorMap.find(colorStr);
	if (iter == m_colorMap.end())
	{
		throw Exception("Invalid color");
	}
	return iter->second;
}