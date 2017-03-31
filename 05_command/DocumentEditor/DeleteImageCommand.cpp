#include "stdafx.h"
#include "DeleteImageCommand.h"

using namespace std;
CDeleteImageCommand::CDeleteImageCommand(std::vector<CDocumentItem>& items, 
	size_t index)
	:m_items(items),
	m_item(m_items[index]),
	m_position(index)
{
}

void CDeleteImageCommand::DoExecute()
{
	m_items.erase(
		next(m_items.begin(), m_position));
	m_item.GetImage()->MustDelete(true);
}

void CDeleteImageCommand::DoUnexecute()
{
	m_items.insert(
		next(m_items.begin(), m_position), m_item);
	m_item.GetImage()->MustDelete(false);
}
