#pragma once
#include "Menu.h"
#include "IDocument.h"

class CEditor
{
public:
	CEditor();
	void Start();

private:
	// Указатель на метод класса CEditor, принимающий istream& и возвращающий void
	typedef void (CEditor::*MenuHandler)(std::istream & in);

	void AddMenuItem(const std::string & shortcut, const std::string & description, MenuHandler handler);

	void SetTitle(std::istream & in);
	void AddParagraph(std::istream & in);
	void AddImage(std::istream & in);
	void ReplaceText(std::istream & in);
	void ResizeImage(std::istream & in);
	void DeleteItem(std::istream & in);
	void Undo(std::istream &);
	void Redo(std::istream &);
	void Save(std::istream & in);
	void List(std::istream &);


	size_t ReadNumber(std::istream & in);
	boost::optional<size_t> ReadPosition(std::istream & in);
	std::string ReadToEndl(std::istream & in);

	CMenu m_menu;
	std::unique_ptr<IDocument> m_document;
};
