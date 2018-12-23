#include "stdafx.h"
#include "Image.h"
#include "WordException.h"

CImage::CImage(const WorkCopyFactory& wcFac)
	: m_wcFac(wcFac)
{
}

std::string CImage::GetPath()const
{
	return m_copy ? m_copy->GetPath().string() : "";
}

void CImage::SetPath(const std::string& path)
{
	m_copy = m_wcFac(path);
}

void CImage::Resize(int width, int height)
{
	if ((width <= 0) || (width > 10000) ||
		(height <= 0) || (height > 10000))
	{
		throw CWordException("Invalid image size");
	}
	m_width = width;
	m_height = height;
}
