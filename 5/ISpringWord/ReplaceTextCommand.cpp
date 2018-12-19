#include "stdafx.h"
#include "ReplaceTextCommand.h"

CReplaceTextCommand::CReplaceTextCommand(std::shared_ptr<IParagraph> paragraph, const std::string& text)
	: m_paragraph(paragraph)
	, m_newText(text)
	, m_oldText(paragraph->GetText())
{
}

void CReplaceTextCommand::DoExecute()
{
	m_paragraph->SetText(m_newText);
}

void CReplaceTextCommand::DoUnexecute()
{
	m_paragraph->SetText(m_oldText);
}
