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

std::shared_ptr<CParagraph> CParagraph::Create(const std::string& text)
{
	auto para = std::make_shared<CParagraph>();
	para->SetText(text)->Execute();
	return para;

}

std::string CParagraph::GetText()const
{
	return m_text;
}
ICommandPtr CParagraph::SetText(const std::string& text)
{
	auto para = shared_from_this();
	return std::make_unique<CReplaceTextCommand>(para, text);


	m_text = text;
}
