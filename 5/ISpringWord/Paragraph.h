#pragma once
#include "ICommandExecutor.h"
#include "IParagraph.h"

class CParagraphImpl;

class CParagraph : public IParagraph, public std::enable_shared_from_this<CParagraph>
{
public:
	CParagraph(ICommandExecutor& commandExecutor, const std::string& text);

	std::string GetText()const override;
	void SetText(const std::string& text) override;

private:
	class CReplaceTextCommand;

	ICommandExecutor& m_commandExecutor;
	std::string m_text;
};

