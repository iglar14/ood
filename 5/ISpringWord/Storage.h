#pragma once
#include "IStorage.h"

class CStorage : public IStorage
{
public:
	CStorage();
	~CStorage() override;

	std::unique_ptr<IWorkCopy> AddFile(const std::string& path) override;

private:
	boost::filesystem::path GetNextFileName(const boost::filesystem::path& ext);

	boost::filesystem::path m_tempDir;
	size_t m_counter = 0;
};
