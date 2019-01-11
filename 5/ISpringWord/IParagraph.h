#pragma once

class IImmutableParagraph
{
public:
	virtual std::string GetText()const = 0;
	virtual ~IImmutableParagraph() = default;
};

class IParagraph : public IImmutableParagraph
{
public:
	virtual void SetText(const std::string& text) = 0;
};
