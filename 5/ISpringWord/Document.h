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

	std::shared_ptr<IImmutableImage> InsertImage(const std::string& path, int width, int height,
		boost::optional<size_t> position = boost::none) override;

	size_t GetItemsCount() const override { return m_items.size(); }
	CDocumentItem GetItem(size_t index) override;
	CConstDocumentItem GetItem(size_t index) const override;

	void DeleteItem(size_t index) override;

	bool CanUndo() const override;	
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;

private:
	void VerifyItemIndex(size_t index) const;

	std::unique_ptr<IStorage> m_storage;
	std::string m_title;
	CHistory m_history;
	std::vector<CDocumentItem> m_items;
};