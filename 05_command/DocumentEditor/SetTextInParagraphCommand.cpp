#include "stdafx.h"
#include "SetTextInParagraphCommand.h"

SetTextInParagraphCommand::SetTextInParagraphCommand(std::shared_ptr<IParagraph>& paragraph, 
	const std::string & text)
	: m_paragraph(paragraph),
	m_text(paragraph->GetText()),
	m_newText(text)
{
}

void SetTextInParagraphCommand::DoExecute()
{
	m_paragraph->SetText(m_newText);
}

void SetTextInParagraphCommand::DoUnexecute()
{
	m_paragraph->SetText(m_text);
}
