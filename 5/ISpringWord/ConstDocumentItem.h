#pragma once
#include "IParagraph.h"
#include "IImage.h"

class CConstDocumentItem
{
public:
	CConstDocumentItem(const std::shared_ptr<IImage>& image);
	CConstDocumentItem(const std::shared_ptr<IParagraph>& paragraph);

	// Возвращает указатель на константное изображение, либо nullptr,
	// если элемент не является изображением
	std::shared_ptr<const IImage> GetImage()const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
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
