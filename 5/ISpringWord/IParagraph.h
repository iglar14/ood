#pragma once
#include "ICommand_fwd.h"

class IImmutableParagraph
{
public:
	virtual std::string GetText()const = 0;
	virtual ~IImmutableParagraph() = default;
};

class IParagraph : public IImmutableParagraph
{
public:
	virtual ICommandPtr SetText(const std::string& text) = 0;
};
