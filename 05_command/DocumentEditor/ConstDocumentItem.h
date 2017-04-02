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
	const std::shared_ptr<IImage> GetImage()const;
	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
	const std::shared_ptr<IParagraph> GetParagraph()const;
	virtual ~CConstDocumentItem() = default;
protected:
	std::shared_ptr<IParagraph> m_paragraph;
	std::shared_ptr<IImage> m_image;
};
