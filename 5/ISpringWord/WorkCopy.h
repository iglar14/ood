#pragma once
#include "IWorkCopy.h"

class CWorkCopy : public IWorkCopy
{
public:
	CWorkCopy(const std::filesystem::path& src, const std::filesystem::path& dest, bool keep = false);
	~CWorkCopy() override;

	std::filesystem::path GetPath() const override;

private:
	std::filesystem::path m_path;
	bool m_keep = false;
};
