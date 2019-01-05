#pragma once
#include "IImage.h"
#include "IWorkCopy.h"

class CImage : public IImage, public std::enable_shared_from_this<CImage>
{
public:
	CImage(std::unique_ptr<IWorkCopy> wc);

	static std::shared_ptr<CImage> Create(std::unique_ptr<IWorkCopy> wc, int width, int height);

	std::string GetPath()const override;

	// ������ ����������� � ��������
	int GetWidth()const { return m_width; };
	// ������ ����������� � ��������
	int GetHeight()const { return m_height; }

	// �������� ������ �����������
	ICommandPtr Resize(int width, int height) override;

private:
	class CResizeImageCommand;
	std::unique_ptr<IWorkCopy> m_copy;
	int m_width = 0;
	int m_height = 0;
};