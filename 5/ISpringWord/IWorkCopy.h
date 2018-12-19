#pragma once

class IWorkCopy
{
public:
	virtual ~IWorkCopy() = default;

	virtual std::string GetPath() const = 0;
};

using WorkCopyFactory = std::function<std::unique_ptr<IWorkCopy>(const std::string&)>;
