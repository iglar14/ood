#pragma once
#include "ConstDocumentItem.h"

class CDocumentItem : public CConstDocumentItem
{
public:
	using CConstDocumentItem::CConstDocumentItem;

	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	using CConstDocumentItem::GetImage;
	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	using CConstDocumentItem::GetParagraph;
};

//using CDocumentItemPtr = std::shared_ptr<CDocumentItem>;
