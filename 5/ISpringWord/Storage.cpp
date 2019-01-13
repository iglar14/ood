#include "stdafx.h"
#include "Storage.h"
#include "WorkCopy.h"
#include <boost/lexical_cast.hpp>

namespace fs = std::filesystem;

static fs::path GetNextFileName(const fs::path& baseDir, const std::string& prefix, const std::string& ext, size_t& index)
{
	fs::path p;
	do
	{
		p = baseDir / (prefix + boost::lexical_cast<std::string>(index++) + ext);
	} while (fs::exists(p));
	return p;
}

CStorage::CStorage()
{
	size_t index = 0;
	m_tempDir = ::GetNextFileName(fs::temp_directory_path(), "iSpringWord-", "", index);
	fs::create_directories(m_tempDir);
}

CStorage::~CStorage()
{
	std::error_code ec;
	fs::remove_all(m_tempDir, ec);
}

std::unique_ptr<IWorkCopy> CStorage::AddFile(const fs::path& fspath)
{
	fs::path dest = GetNextFileName(fspath.extension());
	return std::make_unique<CWorkCopy>(fspath, dest);
}

fs::path CStorage::GetNextFileName(const std::filesystem::path& ext)
{
	return ::GetNextFileName(m_tempDir, "", ext.string(), m_counter);
}
