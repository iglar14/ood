#pragma once

class IWorkCopy
{
public:
	virtual ~IWorkCopy() = default;

	virtual boost::filesystem::path GetPath() const = 0;
};
