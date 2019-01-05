#include "stdafx.h"
#include "Image.h"
#include "AbstractCommand.h"
//#include "FunctionalCommand.h"
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

CImage::CImage(std::unique_ptr<IWorkCopy> wc)
	: m_copy(std::move(wc))
{
}

std::shared_ptr<CImage> CImage::Create(std::unique_ptr<IWorkCopy> wc, int width, int height)
{
	auto img = std::make_shared<CImage>(std::move(wc));
	img->Resize(width, height)->Execute();
	return img;
}

std::string CImage::GetPath()const
{
	return m_copy ? m_copy->GetPath().string() : "";
}

ICommandPtr CImage::Resize(int width, int height)
{
	if ((width <= 0) || (width > 10000) ||
		(height <= 0) || (height > 10000))
	{
		throw CWordException("Invalid image size");
	}
	auto img = shared_from_this();
/*	auto executor = [img, width, height] {
		img->m_width = width;
		img->m_height = height;
	};
	auto unexecutor = [img, width = m_width, height = m_height] {
		img->m_width = width;
		img->m_height = height;
	};
	return std::make_unique<CFunctionalCommand>(executor, unexecutor);*/
	return std::make_unique<CResizeImageCommand>(img, width, height);
}
