#pragma once
#include "AbstractCommand.h"
#include "IImage.h"

class CResizeImageCommand :
	public CAbstractCommand
{
public:
	CResizeImageCommand(std::shared_ptr<IImage> img, int width, int height);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::shared_ptr<IImage> m_img;
	int m_oldWidth, m_oldHeight;
	int m_newWidth, m_newHeight;
};

