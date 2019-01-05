#include "stdafx.h"
#include "Image.h"
#include "WordException.h"

CImage::CImage(std::unique_ptr<IWorkCopy> wc)
	: m_copy(std::move(wc))
{
}

std::string CImage::GetPath()const
{
	return m_copy ? m_copy->GetPath().string() : "";
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
