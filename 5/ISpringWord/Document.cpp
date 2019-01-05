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
	auto paragraph = CParagraph::Create(text);
	CDocumentItem item(paragraph);
	m_history.AddAndExecuteCommand(std::make_unique<CInsertItemCommand>(item, m_items, position));
	return paragraph;
}

void CDocument::ReplaceText(size_t position, const std::string& text)
{
	if (position >= m_items.size())
	{
		throw CWordException("invalid item position");
	}
	auto paragraph = m_items[position].GetParagraph();
	if (!paragraph)
	{
		throw CWordException("Item is not a paragraph");
	}
	m_history.AddAndExecuteCommand(paragraph->SetText(text));
}

std::shared_ptr<IImmutableImage> CDocument::InsertImage(const std::string& path, int width, int height, boost::optional<size_t> position)
{
	auto image = CImage::Create(m_storage->AddFile(path), width, height);
	CDocumentItem item(image);
	m_history.AddAndExecuteCommand(std::make_unique<CInsertItemCommand>(item, m_items, position));
	return image;
}

void CDocument::ResizeImage(size_t position, int width, int height)
{
	if (position >= m_items.size())
	{
		throw CWordException("invalid item position");
	}
	auto image = m_items[position].GetImage();
	if (!image)
	{
		throw CWordException("Item is not an image");
	}
	m_history.AddAndExecuteCommand(image->Resize(width, height));
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