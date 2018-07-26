#pragma once
#include "IShapeFactory.h"
#include "Color.h"

class ShapeFactory : public IShapeFactory
{
public:
	ShapeFactory();
	~ShapeFactory() override;

	CShapeUniquePtr CreateShape(const std::string & description) override;

private:
	Color CreateColor(const std::string& colorStr) const;


	std::map<std::string, Color> m_colorMap;
};
