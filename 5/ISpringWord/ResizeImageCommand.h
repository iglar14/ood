#pragma once
#include "AbstractCommand.h"
#include "IImage.h"

class CResizeImageCommand :
	public CAbstractCommand
{
public:
	CResizeImageCommand(const std::shared_ptr<IImage>& img, int width, int height);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::shared_ptr<IImage> m_img;
	int m_width, m_height;
};

