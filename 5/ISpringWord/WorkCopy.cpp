#include "stdafx.h"
#include "WorkCopy.h"

namespace fs = std::filesystem;

CWorkCopy::CWorkCopy(const fs::path& src, const fs::path& dest, bool keep)
	: m_path(dest)
	, m_keep(keep)
{
	fs::copy_file(src, dest, fs::copy_options::overwrite_existing);
}

CWorkCopy::~CWorkCopy()
{
	if (!m_keep)
	{
		std::error_code ec;
		fs::remove(m_path, ec);
	}
}

fs::path CWorkCopy::GetPath() const
{
	return m_path.string();
}
