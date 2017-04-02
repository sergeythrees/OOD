#include "stdafx.h"
#include "InsertImageCommand.h"

using namespace std;

CInsertImageCommand::CInsertImageCommand(std::vector<CDocumentItem>& items,
	std::shared_ptr<IImage> image, const boost::optional<size_t>& position)
	:m_items(items),
	m_item(CDocumentItem(image)),
	m_position(position)
{
	if (position && *position > m_items.size())
		throw out_of_range("Position is out of range");
}

void CInsertImageCommand::DoExecute()
{
	if (m_position)
		m_items.insert(
			next(m_items.begin(), *m_position), m_item);
	else
		m_items.push_back(m_item);
}

void CInsertImageCommand::DoUnexecute()
{
	if (m_position)
		m_items.erase(
			next(m_items.begin(), *m_position));
	else
		m_items.pop_back();
}
