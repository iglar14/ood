#include "stdafx.h"
#include "ResizeImageCommand.h"

CResizeImageCommand::CResizeImageCommand(const std::shared_ptr<IImage>& img, int width, int height)
	: m_img(img)
	, m_width(width)
	, m_height(height)
{
}

void CResizeImageCommand::DoExecute()
{
	int oldWidth = m_img->GetWidth();
	int oldHeight = m_img->GetHeight();
	m_img->Resize(m_width, m_height);
	m_width = oldWidth;
	m_height = oldHeight;
}

void CResizeImageCommand::DoUnexecute()
{
	DoExecute();
}
