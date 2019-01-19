#include "stdafx.h"
#include "Image.h"
#include "AbstractCommand.h"
#include "WordException.h"

class CImage::CResizeImageCommand :
	public CAbstractCommand
{
public:
	CResizeImageCommand(const std::shared_ptr<CImage>& img, int width, int height)
		: m_img(img)
		, m_width(width)
		, m_height(height)
	{
	}

protected:
	void DoExecute() override
	{
		std::swap(std::tie(m_width, m_height), std::tie(m_img->m_width, m_img->m_height));
	}

	void DoUnexecute() override
	{
		DoExecute();
	}

private:
	std::shared_ptr<CImage> m_img;
	int m_width, m_height;
};

CImage::CImage(ICommandExecutor& commandExecutor, std::unique_ptr<IWorkCopy> wc)
	: m_copy(std::move(wc))
	, m_commandExecutor(commandExecutor)
{
}

std::shared_ptr<CImage> CImage::Create(ICommandExecutor& commandExecutor, std::unique_ptr<IWorkCopy> wc, int width, int height)
{
	auto img = std::shared_ptr<CImage>(new CImage(commandExecutor, std::move(wc)));
	img->ResizeImpl(width, height)->Execute();
	return img;
}

std::string CImage::GetPath()const
{
	return m_copy ? m_copy->GetPath().string() : "";
}

void CImage::Resize(int width, int height)
{
	m_commandExecutor.AddAndExecuteCommand(ResizeImpl(width, height));
}

ICommandPtr CImage::ResizeImpl(int width, int height)
{
	if ((width <= 0) || (width > 10000) ||
		(height <= 0) || (height > 10000))
	{
		throw CWordException("Invalid image size");
	}
	auto img = shared_from_this();
	return std::make_unique<CResizeImageCommand>(img, width, height);
}
