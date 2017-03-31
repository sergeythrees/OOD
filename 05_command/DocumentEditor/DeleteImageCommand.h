#pragma once
#include "stdafx.h"
#include "DocumentItem.h"
#include "AbstractCommand.h"
#include "IImage.h"

class CDeleteImageCommand : public CAbstractCommand
{
public:
	CDeleteImageCommand(std::vector<CDocumentItem> & items, size_t index);
protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::vector<CDocumentItem> & m_items;
	CDocumentItem m_item;
	size_t m_position;
};
