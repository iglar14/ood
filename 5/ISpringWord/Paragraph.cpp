#include "stdafx.h"
#include "Paragraph.h"

std::string CParagraph::GetText()const
{
	return m_text;
}
void CParagraph::SetText(const std::string& text)
{
	m_text = text;
}
