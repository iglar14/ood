#pragma once
#include "IHistory.h"
#include "IParagraph.h"

class CParagraphImpl;

class CParagraph : public IParagraph, public std::enable_shared_from_this<CParagraph>
{
public:
	CParagraph(IHistory& history, const std::string& text);

	std::string GetText()const override;
	void SetText(const std::string& text) override;

private:
	class CReplaceTextCommand;

	IHistory& m_history;
	std::string m_text;
};

