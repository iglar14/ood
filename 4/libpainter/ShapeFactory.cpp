#include "stdafx.h"
#include "ShapeFactory.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Ellipse.h"
#include "RegularPolygon.h"

namespace
{

static PointI GetPoint(boost::smatch xResults, size_t index)
{
	int x = boost::lexical_cast<int>(xResults[index]);
	int y = boost::lexical_cast<int>(xResults[index + 1]);
	return PointI{ x, y };
}

using ColorMap = std::map<std::string, Color>;
static ColorMap CreateColorMap()
{
	ColorMap colorMap;
	colorMap["red"] = Color::Red;
	colorMap["green"] = Color::Green;
	colorMap["blue"] = Color::Blue;
	colorMap["pink"] = Color::Pink;
	colorMap["yellow"] = Color::Yellow;
	colorMap["black"] = Color::Black;
	return colorMap;
}

static const ColorMap s_colorMap = CreateColorMap();

static Color CreateColor(const std::string& colorStr)
{
	auto iter = s_colorMap.find(colorStr);
	if (iter == s_colorMap.end())
	{
		throw IShapeFactory::Exception("Invalid color");
	}
	return iter->second;
}

static const char* REGEXP_RECT = "rectangle\\s+(\\w+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)";
static const char* REGEXP_TRIANGLE = "triangle\\s+(\\w+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)";
static const char* REGEXP_ELLIPSE = "ellipse\\s+(\\w+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)\\s+(\\d+)\\s+(\\d+)";
static const char* REGEXP_POLYGON = "polygon\\s+(\\w+)\\s+([\\+\\-]?\\d+)\\s+([\\+\\-]?\\d+)\\s+(\\d+)\\s+(\\d+)";

static CShapeUniquePtr TryCreateRectangle(const std::string & description)
{
	boost::smatch xResults;
	if (boost::regex_match(description, xResults, boost::regex(REGEXP_RECT)))
	{
		Color color = CreateColor(xResults[1]);
		const PointI lt = GetPoint(xResults, 2);
		const PointI rb = GetPoint(xResults, 4);
		return std::make_unique<CRectangle>(color, lt, rb);
	}
	return nullptr;
}

static CShapeUniquePtr TryCreateTriangle(const std::string & description)
{
	boost::smatch xResults;
	if (boost::regex_match(description, xResults, boost::regex(REGEXP_TRIANGLE)))
	{
		Color color = CreateColor(xResults[1]);
		const PointI v1 = GetPoint(xResults, 2);
		const PointI v2 = GetPoint(xResults, 4);
		const PointI v3 = GetPoint(xResults, 6);
		return std::make_unique<CTriangle>(color, v1, v2, v3);
	}
	return nullptr;
}

static CShapeUniquePtr TryCreateEllipse(const std::string & description)
{
	boost::smatch xResults;
	if (boost::regex_match(description, xResults, boost::regex(REGEXP_ELLIPSE)))
	{
		Color color = CreateColor(xResults[1]);
		const PointI center = GetPoint(xResults, 2);
		const int rx = boost::lexical_cast<int>(xResults[4]);
		const int ry = boost::lexical_cast<int>(xResults[5]);
		return std::make_unique<CEllipse>(color, center, rx, ry);
	}
	return nullptr;
}

static CShapeUniquePtr TryCreatePolygon(const std::string & description)
{
	boost::smatch xResults;
	if (boost::regex_match(description, xResults, boost::regex(REGEXP_POLYGON)))
	{
		Color color = CreateColor(xResults[1]);
		const PointI center = GetPoint(xResults, 2);
		const int radius = boost::lexical_cast<int>(xResults[4]);
		const int count = boost::lexical_cast<int>(xResults[5]);
		return std::make_unique<CRegularPolygon>(color, center, radius, count);
	}
	return nullptr;
}
}

ShapeFactory::ShapeFactory()
{
}

ShapeFactory::~ShapeFactory()
{
}

CShapeUniquePtr ShapeFactory::CreateShape(const std::string & description)
{
	using PCreator = CShapeUniquePtr(const std::string&);
	PCreator* creators[] = { &TryCreateRectangle, &TryCreateTriangle, &TryCreateEllipse, &TryCreatePolygon };
	for (auto creator : creators)
	{
		auto sh = creator(description);
		if (sh)
		{
			return sh;
		}
	}
	return nullptr;
}

