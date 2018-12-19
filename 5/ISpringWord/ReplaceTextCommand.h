#pragma once
#include "AbstractCommand.h"
#include "IParagraph.h"

class CReplaceTextCommand :
	public CAbstractCommand
{
public:
	CReplaceTextCommand(std::shared_ptr<IParagraph> paragraph, const std::string& text);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::shared_ptr<IParagraph> m_paragraph;
	const std::string m_newText, m_oldText;
};

