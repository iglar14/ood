#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"

class CInsertItemCommand :
	public CAbstractCommand
{
public:
	CInsertItemCommand(const CDocumentItem& item, std::vector<CDocumentItem>& vec, boost::optional<size_t> position = boost::none);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	CDocumentItem m_item;
	std::vector<CDocumentItem>& m_vec;
	boost::optional<size_t> m_position;
};

