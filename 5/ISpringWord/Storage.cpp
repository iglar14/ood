#include "stdafx.h"
#include "Storage.h"
#include "WorkCopy.h"
#include <boost/lexical_cast.hpp>

namespace fs = boost::filesystem;

CStorage::CStorage()
{
	m_tempDir = fs::temp_directory_path() / fs::unique_path("iSpringWord-%%%%");
	fs::create_directories(m_tempDir);
}

CStorage::~CStorage()
{
	boost::system::error_code ec;
	fs::remove_all(m_tempDir, ec);
}

std::unique_ptr<IWorkCopy> CStorage::AddFile(const fs::path& fspath)
{
	fs::path dest = GetNextFileName(fspath.extension());
	return std::make_unique<CWorkCopy>(fspath, dest);
}

fs::path CStorage::GetNextFileName(const boost::filesystem::path& ext)
{
	fs::path p;
	do
	{
		p = m_tempDir / boost::lexical_cast<std::string>(m_counter++);
		p += ext;
	} while (fs::exists(p));
	return p;
}
