#include "stdafx.h"
#include <sstream>
#include "Image.h"
#include "Paragraph.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "InsertParagraphCommand.h"
#include "InsertImageCommand.h"
#include "DeleteImageCommand.h"
#include "DeleteParagraphCommand.h"
#include "ResizeImageCommand.h"
#include "SetTextInParagraphCommand.h"
#include "DecodeHtmlEntities.h"

using namespace std;
using namespace boost;
using namespace filesystem;



void CDocument::SetTitle(const std::string & title)
{
	m_history.AddAndExecuteCommand(make_unique<CChangeStringCommand>(m_title, title));
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

std::shared_ptr<IParagraph> CDocument::InsertParagraph(const std::string & text, 
	const boost::optional<size_t>& position)
{
	auto paragraph = make_shared<CParagraph>(text);
	m_history.AddAndExecuteCommand(
		make_unique<CInsertParagraphCommand>(m_items, paragraph, position));
	return paragraph;
}

std::shared_ptr<IImage> CDocument::InsertImage(const std::string & path, 
	int width, int height, 
	const boost::optional<size_t>& position)
{
	auto image = make_shared<CImage>(path, width, height);
	m_history.AddAndExecuteCommand(
		make_unique<CInsertImageCommand>(m_items, image, position));
	return image;
}

void CDocument::ReplaceText(size_t index, const std::string & text)
{
	if (index >= m_items.size())
		throw out_of_range("Position is out of range");

	m_history.AddAndExecuteCommand(
		make_unique<SetTextInParagraphCommand>(
			m_items[index].GetParagraph(), text));
}

void CDocument::ResizeImage(size_t index, int width, int height)
{
	if (index >= m_items.size())
		throw out_of_range("Position is out of range");

	m_history.AddAndExecuteCommand(
		make_unique<CResizeImageCommand>(
			m_items[index].GetImage(), width, height));
}

void CDocument::DeleteItem(size_t index)
{
	if (index >= m_items.size())
		throw out_of_range("Position is out of range");

	if (m_items[index].GetImage() != nullptr)
		m_history.AddAndExecuteCommand(
			make_unique<CDeleteImageCommand>(m_items, index));
	else
		m_history.AddAndExecuteCommand(
			make_unique<DeleteParagraphCommand>(m_items, index));
}

CConstDocumentItem CDocument::GetItem(size_t index) const
{
	if (index >= m_items.size())
		throw out_of_range("Position is out of range");
	
	return *(m_items.begin() + index);
}

CDocumentItem CDocument::GetItem(size_t index)
{
	if (index >= m_items.size())
		throw out_of_range("Position is out of range");

	return *(m_items.begin() + index);
}

size_t CDocument::GetItemsCount() const
{
	return m_items.size();
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	m_history.Redo();
}

void CDocument::Save(const std::string & filePath) const
{
	path docPath(filePath);
	
	if (docPath.has_parent_path())
		create_directories(docPath.parent_path());

	std::ofstream out(filePath);
	stringstream body;
	for (auto item : m_items)
	{
		if (item.GetParagraph())
		{
			body << "    <p>" 
				<< DecodeToHtml(item.GetParagraph()->GetText()) 
				<< "</p>" << endl;
		}
		else if (item.GetImage())
		{
			auto image = item.GetImage();
			body << "    <img src=\"" << image->GetPath()
				<< "\" height=\"" << image->GetHeight()
				<< "\" width=\"" << image->GetWidth()
				<< "\">" << endl;
			create_directories(docPath.parent_path() / "images");
			image->Save(docPath.parent_path().generic_string());
		}
	}

	out << "<!DOCTYPE html>\n<html>\n<head>" << endl 
		 << "<title>" << DecodeToHtml(GetTitle()) << "</title>\n</head>\n"
		 << "<body>\n" << body.str() << "</body>\n</html>";
}
