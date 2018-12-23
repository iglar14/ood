#pragma once
#include "IWorkCopy.h"

class IStorage
{
public:
	virtual ~IStorage() = default;

	virtual std::unique_ptr<IWorkCopy> AddFile(const boost::filesystem::path& path) = 0;
};