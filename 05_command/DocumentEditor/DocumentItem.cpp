#include "stdafx.h"
#include "DocumentItem.h"

CDocumentItem::CDocumentItem(const std::shared_ptr<IParagraph>& paragraph)
	:CConstDocumentItem(paragraph)
{
}
CDocumentItem::CDocumentItem(const std::shared_ptr<IImage>& image)
	: CConstDocumentItem(image)
{
}

std::shared_ptr<IImage> CDocumentItem::GetImage()
{
	return m_image;
}

std::shared_ptr<IParagraph> CDocumentItem::GetParagraph()
{
	return m_paragraph;
}
