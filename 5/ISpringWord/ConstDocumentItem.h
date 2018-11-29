#pragma once
#include "IParagraph.h"
#include "IImage.h"

class CConstDocumentItem
{
public:
	CConstDocumentItem(const std::shared_ptr<IImage>& image);
	CConstDocumentItem(const std::shared_ptr<IParagraph>& paragraph);

	// ���������� ��������� �� ����������� �����������, ���� nullptr,
	// ���� ������� �� �������� ������������
	std::shared_ptr<const IImage> GetImage()const;
	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<const IParagraph> GetParagraph()const;
	virtual ~CConstDocumentItem() = default;

protected:
	std::shared_ptr<IImage> GetImage();
	std::shared_ptr<IParagraph> GetParagraph();

private:
	std::shared_ptr<IImage> m_image;
	std::shared_ptr<IParagraph> m_paragraph;
};

//using CConstDocumentItemPtr = std::shared_ptr<CConstDocumentItem>;
