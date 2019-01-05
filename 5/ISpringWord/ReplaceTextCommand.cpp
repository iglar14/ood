#include "stdafx.h"
#include "ReplaceTextCommand.h"

CReplaceTextCommand::CReplaceTextCommand(const std::shared_ptr<IParagraph>& paragraph, const std::string& text)
	: m_paragraph(paragraph)
	, m_text(text)
{
}

void CReplaceTextCommand::DoExecute()
{
	std::string oldText = m_paragraph->GetText();
	m_paragraph->SetText(m_text);
	m_text = std::move(oldText);
}

void CReplaceTextCommand::DoUnexecute()
{
	DoExecute();
}
