#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"

class CInsertItemCommand :
	public CAbstractCommand
{
public:
	CInsertItemCommand(const CDocumentItem& item, std::vector<CDocumentItem>& vec, std::optional<size_t> position = std::nullopt);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	CDocumentItem m_item;
	std::vector<CDocumentItem>& m_vec;
	std::optional<size_t> m_position;
};

