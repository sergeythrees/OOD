#include "stdafx.h"
#include "Editor.h"
#include "Document.h"

using namespace std;
using namespace std::placeholders;

CEditor::CEditor()
	:m_document(make_unique<CDocument>())
{
	AddMenuItem("setTitle", "Set title. Args: <new title>", &CEditor::SetTitle);
	AddMenuItem("insertParagraph", "Add paragraph. Args: <position>|end <text>", &CEditor::AddParagraph);
	AddMenuItem("insertImage", "Add image. Args: <position>|end <width> <height> <path>", &CEditor::AddImage);
	AddMenuItem("replaceText", "Replace text. Args: <position>", &CEditor::ReplaceText);
	AddMenuItem("resizeImage", "Resize image. Args: <position> <width> <height>", &CEditor::ResizeImage);
	AddMenuItem("deleteItem", "Delete item. Args: <position>", &CEditor::DeleteItem);
	AddMenuItem("undo", "Undo command", &CEditor::Undo);
	AddMenuItem("redo", "Redo command", &CEditor::Redo);
	AddMenuItem("save", "Save document in html. Args: <path>", &CEditor::Save);
	AddMenuItem("list", "List document entities", &CEditor::List);
	m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
	m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
}

void CEditor::Start()
{
	m_menu.Run();
}

void CEditor::AddMenuItem(const string & shortcut, const string & description, MenuHandler handler)
{
	m_menu.AddItem(shortcut, description, bind(handler, this, _1));
}

void CEditor::SetTitle(istream & in)
{
	m_document->SetTitle(ReadToEndl(in));
}

void CEditor::AddParagraph(istream & in)
{
	auto position = ReadPosition(in);
	m_document->InsertParagraph(ReadToEndl(in), position);
}

void CEditor::AddImage(istream & in)
{
	auto position = ReadPosition(in);
	auto width = ReadNumber(in);
	auto height = ReadNumber(in);
	string path = ReadToEndl(in);

	m_document->InsertImage(path, width, height, position);
}

void CEditor::DeleteItem(istream & in)
{
	m_document->DeleteItem(static_cast<size_t>(ReadNumber(in)));
}

void CEditor::ReplaceText(istream & in)
{
	auto index = static_cast<size_t>(ReadNumber(in));

	auto item = m_document->GetItem(index);
	if (!item.GetParagraph())
		throw invalid_argument("It's not paragraph");

	m_document->ReplaceText(index, ReadToEndl(in));
}

void CEditor::ResizeImage(istream & in)
{
	auto index = static_cast<size_t>(ReadNumber(in));
	auto width = ReadNumber(in);
	auto height = ReadNumber(in);

	auto item = m_document->GetItem(index);
	if (!item.GetImage())
		throw invalid_argument("It's not image");

	m_document->ResizeImage(index, width, height);
}

void CEditor::Save(istream & in)
{
	m_document->Save(ReadToEndl(in));
}

void CEditor::List(istream &)
{
	cout << "-------------" << endl;
	cout << m_document->GetTitle() << endl;
	for (size_t i = 0; i < m_document->GetItemsCount(); i++)
	{
		auto item = m_document->GetItem(i);
		if (item.GetParagraph())
		{
			cout << i << ". Paragraph: " << item.GetParagraph()->GetText() << endl;
		}
		else
		{
			auto image = item.GetImage();
			cout << i << ". Image: " << image->GetWidth() << "x" 
				<< image->GetHeight() << " " << image->GetPath() << endl;
		}
	}
	cout << "-------------" << endl;
}

void CEditor::Undo(istream &)
{
	if (m_document->CanUndo())
		m_document->Undo();
	else
		cout << "Can't undo" << endl;
}

void CEditor::Redo(istream &)
{
	if (m_document->CanRedo())
		m_document->Redo();
	else
		cout << "Can't redo" << endl;
}

unsigned CEditor::ReadNumber(istream & in)
{
	unsigned number;
	if (!(in >> number))
		throw invalid_argument(
			"It is not positive number");

	return number;
}

boost::optional<size_t> CEditor::ReadPosition(istream & in)
{
	boost::optional<size_t> position;
	string pos;
	in >> pos;
	if (pos != "end") try
	{
		position = stoul(pos);
	}
	catch (...)
	{
		throw invalid_argument(
			"Value should be a positive number or 'end'"); 
	}

	return position;
}

string CEditor::ReadToEndl(istream & in)
{
	in.get();
	string result;
	getline(in, result);
	return result;
}

