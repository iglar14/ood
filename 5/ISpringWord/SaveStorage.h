#pragma once
#include "IStorage.h"

class CSaveStorage : public IStorage
{
public:
	CSaveStorage(const boost::filesystem::path& outFilePath);
	~CSaveStorage() override;

	std::unique_ptr<IWorkCopy> AddFile(const boost::filesystem::path& path) override;

private:
	boost::filesystem::path m_dir;
};
