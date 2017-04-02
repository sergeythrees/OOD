#pragma once
#include "stdafx.h"
#include "IParagraph.h"
#include "AbstractCommand.h"

class SetTextInParagraphCommand : public CAbstractCommand
{
public:
	SetTextInParagraphCommand(std::shared_ptr<IParagraph>& paragraph, const std::string& text);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::shared_ptr<IParagraph> m_paragraph;
	std::string m_text;
	std::string m_newText;
};
