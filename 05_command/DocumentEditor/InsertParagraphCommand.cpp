#include "stdafx.h"
#include "InsertParagraphCommand.h"

using namespace std;

CInsertParagraphCommand::CInsertParagraphCommand(std::vector<CDocumentItem>& items,
	std::shared_ptr<IParagraph> paragraph, const boost::optional<size_t>& position)
	:m_items(items),
	m_item(CDocumentItem(paragraph)),
	m_position(position)
{
	if (position && *position > m_items.size())
		throw out_of_range("Position is out of range");
}

void CInsertParagraphCommand::DoExecute()
{
	if (m_position)
		m_items.insert(
			next(m_items.begin(), *m_position), m_item);
	else
		m_items.push_back(m_item);
}

void CInsertParagraphCommand::DoUnexecute()
{
	if (m_position)
		m_items.erase(next(m_items.begin(), *m_position));
	else
		m_items.pop_back();
}
