#pragma once
#include "IImage.h"
#include "History.h"

class CImage : public IImage
{
public:
	CImage(const std::string & path, int width, int height);
	~CImage();

	std::string GetPath()const override;
	int GetWidth()const override;
	int GetHeight()const override;
	void Resize(int width, int height) override;
	void Save(const std::string & path) override;

private:
	std::string m_fileName;
	int m_width;
	int m_height;
};