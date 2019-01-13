#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"

class CDeleteItemCommand :
	public CAbstractCommand
{
public:
	CDeleteItemCommand(std::vector<CDocumentItem>& vec, size_t position);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::optional<CDocumentItem> m_item;
	std::vector<CDocumentItem>& m_vec;
	size_t m_position;
};

