#pragma once
#include "../ISpringWord/IStorage.h"

struct MockWorkCopy : public IWorkCopy
{
	MockWorkCopy(const boost::filesystem::path& path)
		: m_path(path)
	{
	}
	boost::filesystem::path GetPath() const override
	{
		return m_path;
	}

	boost::filesystem::path m_path;
};

struct MockStorage : public IStorage
{
	std::unique_ptr<IWorkCopy> AddFile(const boost::filesystem::path& path) override
	{
		return std::make_unique<MockWorkCopy>(path);
	}
};
