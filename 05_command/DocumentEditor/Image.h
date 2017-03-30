#pragma once
#include "IImage.h"
#include "History.h"

class CImage : public IImage
{
public:
	CImage(const std::string & path, int width, int height, CHistory & history);
	~CImage();

	std::string GetPath()const override;
	int GetWidth()const override;
	int GetHeight()const override;
	void Resize(int width, int height) override;
	void MustDelete(bool mustDelete) override;

private:
	bool m_mustDelete;
	std::string m_fileName;
	int m_width;
	int m_height;
	CHistory & m_history;
};