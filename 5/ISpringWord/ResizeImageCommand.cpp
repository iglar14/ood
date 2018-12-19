#include "stdafx.h"
#include "ResizeImageCommand.h"

CResizeImageCommand::CResizeImageCommand(std::shared_ptr<IImage> img, int width, int height)
	: m_img(img)
	, m_oldWidth(m_img->GetWidth())
	, m_oldHeight(m_img->GetHeight())
	, m_newWidth(width)
	, m_newHeight(height)
{
}

void CResizeImageCommand::DoExecute()
{
	m_img->Resize(m_newWidth, m_newHeight);
}

void CResizeImageCommand::DoUnexecute()
{
	m_img->Resize(m_oldWidth, m_oldHeight);
}
