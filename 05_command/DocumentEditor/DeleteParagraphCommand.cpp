#include "stdafx.h"
#include <iterator>
#include "DeleteParagraphCommand.h"

using namespace std;
DeleteParagraphCommand::DeleteParagraphCommand(std::vector<CDocumentItem> & items,
	size_t index)
	:m_items(items),
	m_item(m_items[index]),
	m_position(index)
{
}

void DeleteParagraphCommand::DoExecute()
{
	m_items.erase(next(m_items.begin(), m_position));
}

void DeleteParagraphCommand::DoUnexecute()
{
	m_items.insert(next(m_items.begin(), m_position), m_item);
}
