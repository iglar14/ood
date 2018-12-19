#pragma once
#include <stdexcept>

class CWordException : public std::runtime_error
{
public:
	CWordException(const std::string& descr)
		: std::runtime_error(descr)
	{
	}
};