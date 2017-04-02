#include "stdafx.h"
#include "ResizeImageCommand.h"
#include "Image.h"

using namespace std;
using namespace boost;
using namespace filesystem;

CImage::CImage(const string & filePath, int width, int height)
	:m_width(width),
	m_height(height)
{
	if (!exists(path(filePath)))
		throw invalid_argument("Invalid file path or not accessible file");

	m_fileName = filesystem::unique_path().filename().generic_string() 
		+ path(filePath).filename().extension().generic_string();
	create_directories(temp_directory_path() / "images");
	copy_file(filePath, temp_directory_path() / "images" / m_fileName, copy_option::overwrite_if_exists);
}

CImage::~CImage() try
{
	remove(temp_directory_path() / "images" / m_fileName);
}
catch(...) {}

std::string CImage::GetPath() const
{
	return (path("images") / m_fileName).generic_string();
}

int CImage::GetWidth() const
{
	return m_width;
}

int CImage::GetHeight() const
{
	return m_height;
}

void CImage::Resize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void CImage::Save(const std::string & path)
{
	copy_file(temp_directory_path() / GetPath(),
		filesystem::path(path) / GetPath(), copy_option::overwrite_if_exists);
}
