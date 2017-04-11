#include "stdafx.h"
#include "InsertItemCommand.h"

using namespace std;

CInsertItemCommand::CInsertItemCommand(std::vector<std::shared_ptr<CDocumentItem>>& items,
	shared_ptr<CDocumentItem>& item, const boost::optional<size_t>& position)
	:m_items(items),
	m_item(item),
	m_position(position)
{
	if (position && *position > m_items.size())
		throw out_of_range("Position is out of range");
}

void CInsertItemCommand::DoExecute()
{
	if (m_position)
		m_items.insert(m_items.begin() + *m_position, m_item);
	else
		m_items.push_back(m_item);
}

void CInsertItemCommand::DoUnexecute()
{
	if (m_position)
		m_items.erase(m_items.begin() + *m_position);
	else
		m_items.pop_back();
}
