#pragma once
#include "../ISpringWord/IStorage.h"

struct MockWorkCopy : public IWorkCopy
{
	MockWorkCopy(const std::filesystem::path& path)
		: m_path(path)
	{
	}
	std::filesystem::path GetPath() const override
	{
		return m_path;
	}

	std::filesystem::path m_path;
};

struct MockStorage : public IStorage
{
	std::unique_ptr<IWorkCopy> AddFile(const std::filesystem::path& path) override
	{
		return std::make_unique<MockWorkCopy>(path);
	}
};
