#pragma once
#include <memory>
#include "IParagraph.h"

class CParagraphImpl;

class CParagraph : public IParagraph
{
public:
	std::string GetText()const override;
	void SetText(const std::string& text) override;

private:
	std::string m_text;
};

