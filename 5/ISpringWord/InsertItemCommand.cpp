#include "stdafx.h"
#include "InsertItemCommand.h"
#include "WordException.h"

CInsertItemCommand::CInsertItemCommand(const CDocumentItem& item, std::vector<CDocumentItem>& vec, boost::optional<size_t> position)
	: m_position(position)
	, m_vec(vec)
	, m_item(item)
{
	if (m_position && (*m_position > m_vec.size()))
	{
		throw CWordException("invalid item position");
	}
}

void CInsertItemCommand::DoExecute()
{
	if (m_position)
	{
		m_vec.insert(m_vec.begin() + *m_position, m_item);
	}
	else
	{
		m_vec.push_back(m_item);
	}
}

void CInsertItemCommand::DoUnexecute()
{
	if (m_position)
	{
		m_vec.erase(m_vec.begin() + *m_position);
	}
	else
	{
		m_vec.pop_back();
	}
}
