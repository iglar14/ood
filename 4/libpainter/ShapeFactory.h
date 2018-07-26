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

// 	CShapeUniquePtr TryCreateRectangle(const std::string & description);
// 	CShapeUniquePtr TryCreateTriangle(const std::string & description);
// 	CShapeUniquePtr TryCreateEllipse(const std::string & description);
// 	CShapeUniquePtr TryCreatePolygon(const std::string & description);

};
