#pragma once
#include "IShapeFactory.h"

class ShapeFactory : public IShapeFactory
{
public:
	ShapeFactory();
	~ShapeFactory() override;

	std::unique_ptr<CShape> CreateShape(const std::string & description) override;

private:

};
