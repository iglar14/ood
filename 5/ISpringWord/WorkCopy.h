#pragma once
#include "IWorkCopy.h"

class CWorkCopy : public IWorkCopy
{
public:
	CWorkCopy(const boost::filesystem::path& src, const boost::filesystem::path& dest, bool keep = false);
	~CWorkCopy() override;

	boost::filesystem::path GetPath() const override;

private:
	boost::filesystem::path m_path;
	bool m_keep = false;
};
