#pragma once
#include "IDocument.h"
#include "History.h"

class CDocument : public IDocument
{
public:
	void SetTitle(const std::string & title) override;
	std::string GetTitle() const override;

	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text, boost::optional<size_t> position = boost::none) override;

	size_t GetItemsCount() const override { return m_items.empty(); }
	CDocumentItem GetItem(size_t index) override { return m_items[index]; }
	CConstDocumentItem GetItem(size_t index) const override { return m_items[index]; }

	bool CanUndo() const override;	
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;

private:
	std::string m_title;
	CHistory m_history;
	std::vector<CDocumentItem> m_items;
};