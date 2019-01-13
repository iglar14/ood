#pragma once
#include "IStorage.h"

class CSaveStorage : public IStorage
{
public:
	CSaveStorage(const std::filesystem::path& outFilePath);
	~CSaveStorage() override;

	std::unique_ptr<IWorkCopy> AddFile(const std::filesystem::path& path) override;

private:
	std::filesystem::path m_dir;
};
