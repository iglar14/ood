#pragma once
#include "../ISpringWord/IStorage.h"

struct MockWorkCopy : public IWorkCopy
{
	MockWorkCopy(const std::string& path)
		: m_path(path)
	{
	}
	std::string GetPath() const override
	{
		return m_path;
	}

	std::string m_path;
};

struct MockStorage : public IStorage
{
	std::unique_ptr<IWorkCopy> AddFile(const std::string& path) override
	{
		return std::make_unique<MockWorkCopy>(path);
	}
};
