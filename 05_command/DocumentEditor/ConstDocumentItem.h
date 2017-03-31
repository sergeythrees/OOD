#pragma once
#include <memory>
#include <string>
#include "IParagraph.h"
#include "IImage.h"

class CConstDocumentItem
{
public:
	CConstDocumentItem(std::shared_ptr<IParagraph> paragraph);
	CConstDocumentItem(std::shared_ptr<IImage> image);
	// ���������� ��������� �� ����������� �����������, ���� nullptr,
	// ���� ������� �� �������� ������������
	std::shared_ptr<const IImage> GetImage()const;
	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<const IParagraph> GetParagraph()const;
	virtual ~CConstDocumentItem() = default;
protected:
	std::shared_ptr<IParagraph> m_paragraph;
	std::shared_ptr<IImage> m_image;
};
