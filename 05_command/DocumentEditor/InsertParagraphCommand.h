#pragma once
#include "stdafx.h"
#include "DocumentItem.h"
#include "AbstractCommand.h"
#include "IParagraph.h"

class CInsertParagraphCommand : public CAbstractCommand
{
public:
	CInsertParagraphCommand(std::vector<CDocumentItem> & items, 
		std::shared_ptr<IParagraph> paragraph, const boost::optional<size_t>& position);
protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::vector<CDocumentItem> & m_items;
	CDocumentItem m_item;
	boost::optional<size_t> m_position;
};

