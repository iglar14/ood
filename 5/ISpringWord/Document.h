#pragma once
#include "IDocument.h"
#include "IStorage.h"
#include "History.h"

class CDocument : public IDocument
{
public:
	CDocument(std::unique_ptr<IStorage> storage);

	void SetTitle(const std::string & title) override;
	std::string GetTitle() const override;

	std::shared_ptr<IImmutableParagraph> InsertParagraph(const std::string& text, boost::optional<size_t> position = boost::none) override;
	void ReplaceText(size_t position, const std::string& text) override;

	std::shared_ptr<IImmutableImage> InsertImage(const std::string& path, int width, int height,
		boost::optional<size_t> position = boost::none) override;
	void ResizeImage(size_t position, int width, int height) override;

	size_t GetItemsCount() const override { return m_items.size(); }
	CDocumentItem GetItem(size_t index) override { return m_items[index]; }
	CConstDocumentItem GetItem(size_t index) const override { return m_items[index]; }

	void DeleteItem(size_t index) override;

	bool CanUndo() const override;	
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;

private:
	std::unique_ptr<IStorage> m_storage;
	std::string m_title;
	CHistory m_history;
	std::vector<CDocumentItem> m_items;
};