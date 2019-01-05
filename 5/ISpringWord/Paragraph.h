#pragma once
#include "IParagraph.h"

class CParagraphImpl;

class CParagraph : public IParagraph, public std::enable_shared_from_this<CParagraph>
{
public:
	static std::shared_ptr<CParagraph> Create(const std::string& text);

	std::string GetText()const override;
	ICommandPtr SetText(const std::string& text) override;

private:
	class CReplaceTextCommand;

	std::string m_text;
};

