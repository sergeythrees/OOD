#pragma once
#include "stdafx.h"
#include "DocumentItem.h"
#include "AbstractCommand.h"

class CInsertItemCommand : public CAbstractCommand
{
public:
	CInsertItemCommand(std::vector<std::shared_ptr<CDocumentItem>> & items,
		std::shared_ptr<CDocumentItem>& item, const boost::optional<size_t>& position);
protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::vector<std::shared_ptr<CDocumentItem>> & m_items;
	std::shared_ptr<CDocumentItem> m_item;
	boost::optional<size_t> m_position;
};

