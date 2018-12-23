#pragma once

class IWorkCopy
{
public:
	virtual ~IWorkCopy() = default;

	virtual boost::filesystem::path GetPath() const = 0;
};

using WorkCopyFactory = std::function<std::unique_ptr<IWorkCopy>(const boost::filesystem::path&)>;
