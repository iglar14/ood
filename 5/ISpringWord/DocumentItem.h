#pragma once
#include "ConstDocumentItem.h"

class CDocumentItem : public CConstDocumentItem
{
public:
	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	using CConstDocumentItem::GetImage;
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	using CConstDocumentItem::GetParagraph;
};

//using CDocumentItemPtr = std::shared_ptr<CDocumentItem>;
