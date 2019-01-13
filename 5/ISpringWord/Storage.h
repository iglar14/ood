#pragma once
#include "IStorage.h"

class CStorage : public IStorage
{
public:
	CStorage();
	~CStorage() override;

	std::unique_ptr<IWorkCopy> AddFile(const std::filesystem::path& path) override;

private:
	std::filesystem::path GetNextFileName(const std::filesystem::path& ext);

	std::filesystem::path m_tempDir;
	size_t m_counter = 0;
};
