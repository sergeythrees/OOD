#include "stdafx.h"
#include "ResizeImageCommand.h"

using namespace std;

CResizeImageCommand::CResizeImageCommand(std::shared_ptr<IImage> image,
	int newWidth, int newHeight)
	: m_width(image->GetWidth()), m_height(image->GetHeight()),
	m_newWidth(newWidth) ,m_newHeight(newHeight)
{
}

void CResizeImageCommand::DoExecute()
{
	m_image->Resize(m_newWidth, m_newHeight);
}

void CResizeImageCommand::DoUnexecute()
{
	m_image->Resize(m_width, m_height);
}