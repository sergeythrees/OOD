#pragma once
#include "stdafx.h"
#include "IImage.h"
#include "AbstractCommand.h"

class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(std::shared_ptr<IImage> image, int newWidth, int newHeight);

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::shared_ptr<IImage> m_image;
	int m_width;
	int m_height;
	int m_newWidth;
	int m_newHeight;
};
