#include "stdafx.h"
#include "ResizeImageCommand.h"
#include "Image.h"

using namespace std;
using namespace boost;
using namespace filesystem;

CImage::CImage(const string & filePath, int width, int height, CHistory & history)
	:m_fileName(path(filePath).filename().generic_string()),
	m_mustDelete(false),
	m_width(width),
	m_height(height),
	m_history(history)
{
	create_directory(path("images"));
	copy_file(path(filePath), path("images") / m_fileName, copy_option::overwrite_if_exists);
}

CImage::~CImage()
{
	if (m_mustDelete)
		remove(path("images") / m_fileName);
}

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
	m_history.AddAndExecuteCommand(
		make_unique<CResizeImageCommand>(m_width, m_height, width, height));
}

void CImage::MustDelete(bool mustDelete)
{
	m_mustDelete = mustDelete;
}
