#pragma once
#include <iosfwd>
#include "IShapeFactory.h"
#include "PictureDraft.h"

class CDesigner
{
public:
	CDesigner(IShapeFactory & factory);
	~CDesigner();
	CPictureDraft CreateDraft(std::istream & inputData);
private:
	IShapeFactory & m_factory;
};

