#pragma once
#include <memory>
#include <string>
#include "IParagraph.h"
#include "IImage.h"

class CConstDocumentItem
{
public:
	CConstDocumentItem(std::shared_ptr<IParagraph>const& paragraph);
	CConstDocumentItem(std::shared_ptr<IImage>const& image);
	// Возвращает указатель на константное изображение, либо nullptr,
	// если элемент не является изображением
	const std::shared_ptr<IImage> GetImage()const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	const std::shared_ptr<IParagraph> GetParagraph()const;
	virtual ~CConstDocumentItem() = default;
protected:
	std::shared_ptr<IParagraph> m_paragraph;
	std::shared_ptr<IImage> m_image;
};
