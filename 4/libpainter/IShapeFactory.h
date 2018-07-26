#pragma once
#include <memory>
#include <string>

class CShape;
using CShapePtr = std::shared_ptr<CShape>;
using CShapeUniquePtr = std::unique_ptr<CShape>;

struct IShapeFactory
{
	class Exception : public std::exception
	{
	public:
		using std::exception::exception;
	};

	virtual CShapeUniquePtr CreateShape(const std::string & description) = 0;

	virtual ~IShapeFactory() = default;
};