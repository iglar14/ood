#include "stdafx.h"
#include "DeleteItemCommand.h"
#include "WordException.h"

CDeleteItemCommand::CDeleteItemCommand(std::vector<CDocumentItem>& vec, size_t position)
	: m_position(position)
	, m_vec(vec)
{
	if (m_position >= m_vec.size())
	{
		throw CWordException("invalid item position");
	}
	m_item = m_vec[position];
}

void CDeleteItemCommand::DoExecute()
{
	m_vec.erase(m_vec.begin() + m_position);
}

void CDeleteItemCommand::DoUnexecute()
{
	m_vec.insert(m_vec.begin() + m_position, *m_item);
}
