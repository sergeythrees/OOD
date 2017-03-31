#include "stdafx.h"
#include "Paragraph.h"
#include "ChangeStringCommand.h"

using namespace std;

CParagraph::CParagraph(const string & text)
	: m_text(text)
{
}

string CParagraph::GetText() const
{
	return m_text;
}

void CParagraph::SetText(const string & text)
{
	m_text = text;
}

