#include "stdafx.h"
#include <iterator>
#include "DeleteItemCommand.h"

using namespace std;
DeleteItemCommand::DeleteItemCommand(std::vector<std::shared_ptr<CDocumentItem>> & items,
	size_t index)
	:m_items(items),
	m_item(m_items[index]),
	m_position(index)
{
}

void DeleteItemCommand::DoExecute()
{
	m_items.erase(m_items.begin() + m_position);
}

void DeleteItemCommand::DoUnexecute()
{
	m_items.insert(m_items.begin()+ m_position, m_item);
}
