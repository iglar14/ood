#include "stdafx.h"
#include "ConstDocumentItem.h"

CConstDocumentItem::CConstDocumentItem(const std::shared_ptr<IImage>& image)
	: m_image(image)
{
}

CConstDocumentItem::CConstDocumentItem(const std::shared_ptr<IParagraph>& paragraph)
	: m_paragraph(paragraph)
{
}

std::shared_ptr<const IImage> CConstDocumentItem::GetImage()const
{
	return m_image;
}

std::shared_ptr<IImage> CConstDocumentItem::GetImage()
{
	return m_image;
}

std::shared_ptr<const IParagraph> CConstDocumentItem::GetParagraph()const
{
	return m_paragraph;
}

std::shared_ptr<IParagraph> CConstDocumentItem::GetParagraph()
{
	return m_paragraph;
}
