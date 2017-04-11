#pragma once
#include "stdafx.h"
#include "DocumentItem.h"
#include "AbstractCommand.h"

class DeleteItemCommand : public CAbstractCommand
{
public:
	DeleteItemCommand(std::vector<std::shared_ptr<CDocumentItem>> & items,
		size_t index);
protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::vector<std::shared_ptr<CDocumentItem>> & m_items;
	std::shared_ptr<CDocumentItem> m_item;
	size_t m_position;
};
