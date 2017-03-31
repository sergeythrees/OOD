#pragma once
#include "stdafx.h"
#include "DocumentItem.h"
#include "IDocument.h"
#include "History.h"

class CDocument:public IDocument
{
public:
	CDocument(const std::string& title, CHistory& history);
	void SetTitle(const std::string & title) override;
	std::string GetTitle() const override;

	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		boost::optional<size_t> position = boost::none) override;

	std::shared_ptr<IImage> InsertImage(const std::string& path, int width, int height,
		boost::optional<size_t> position = boost::none);
	
	void DeleteItem(size_t index) override;

	CConstDocumentItem GetItem(size_t index)const override;
	CDocumentItem GetItem(size_t index) override;

	size_t GetItemsCount()const;
	bool CanUndo() const override;	
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;

	void Save(std::ostream& out) const;
private:
	std::vector<CDocumentItem> m_items;
	std::string m_title;
	CHistory& m_history;
};