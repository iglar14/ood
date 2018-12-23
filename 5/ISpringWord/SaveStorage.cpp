#include "stdafx.h"
#include "SaveStorage.h"
#include "WorkCopy.h"

namespace fs = boost::filesystem;

CSaveStorage::CSaveStorage(const fs::path& outFilePath)
{
	fs::path outDir = outFilePath.parent_path() / outFilePath.stem();
	outDir += "-images";
	m_dir = outDir;
}

CSaveStorage::~CSaveStorage() = default;

std::unique_ptr<IWorkCopy> CSaveStorage::AddFile(const fs::path& path)
{
	fs::create_directory(m_dir);
	return std::make_unique<CWorkCopy>(path, m_dir / path.filename(), true);
}
