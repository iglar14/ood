#pragma once

class IWorkCopy
{
public:
	virtual ~IWorkCopy() = default;

	virtual std::filesystem::path GetPath() const = 0;
};
