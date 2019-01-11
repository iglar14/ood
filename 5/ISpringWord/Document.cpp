#include "stdafx.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "DeleteItemCommand.h"
#include "InsertItemCommand.h"
#include "Paragraph.h"
#include "WordException.h"
#include "Image.h"

using namespace std;

CDocument::CDocument(std::unique_ptr<IStorage> storage)
	: m_storage(move(storage))
{
}

void CDocument::SetTitle(const std::string & title)
{
	m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(m_title, title));
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

std::shared_ptr<IImmutableParagraph> CDocument::InsertParagraph(const std::string& text, boost::optional<size_t> position)
{
	auto paragraph = std::make_shared<CParagraph>(m_history, text);
	CDocumentItem item(paragraph);
	m_history.AddAndExecuteCommand(std::make_unique<CInsertItemCommand>(item, m_items, position));
	return paragraph;
}

std::shared_ptr<IImmutableImage> CDocument::InsertImage(const std::string& path, int width, int height, boost::optional<size_t> position)
{
	auto image = CImage::Create(m_history, m_storage->AddFile(path), width, height);
	CDocumentItem item(image);
	m_history.AddAndExecuteCommand(std::make_unique<CInsertItemCommand>(item, m_items, position));
	return image;
}

CDocumentItem CDocument::GetItem(size_t index)
{
	VerifyItemIndex(index);
	return m_items[index];
}
CConstDocumentItem CDocument::GetItem(size_t index) const
{
	VerifyItemIndex(index);
	return m_items[index];
}

void CDocument::DeleteItem(size_t index)
{
	m_history.AddAndExecuteCommand(std::make_unique<CDeleteItemCommand>(m_items, index));
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	m_history.Redo();
}

void CDocument::VerifyItemIndex(size_t index) const
{
	if (index >= GetItemsCount())
	{
		throw CWordException("invalid item position");
	}
}
