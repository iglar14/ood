#include "stdafx.h"
#include "Paragraph.h"
#include "AbstractCommand.h"

class CParagraph::CReplaceTextCommand :
	public CAbstractCommand
{
public:
	CReplaceTextCommand(const std::shared_ptr<CParagraph>& paragraph, const std::string& text)
		: m_paragraph(paragraph)
		, m_text(text)
	{
	}

protected:
	void DoExecute() override
	{
		std::swap(m_text, m_paragraph->m_text);
	}
	void DoUnexecute() override
	{
		DoExecute();
	}

private:
	std::shared_ptr<CParagraph> m_paragraph;
	std::string m_text;
};

CParagraph::CParagraph(IHistory& history, const std::string& text)
	: m_history(history)
	, m_text(text)
{
}

std::string CParagraph::GetText()const
{
	return m_text;
}
void CParagraph::SetText(const std::string& text)
{
	auto thisPara = shared_from_this();
	m_history.AddAndExecuteCommand(std::make_unique<CReplaceTextCommand>(thisPara, text));
}
