#pragma once
#include "IPainter.h"

class CPainter : public IPainter
{
public:
	~CPainter() = default;
	void DrawPicture(const CPictureDraft& picture, ICanvas& canvas) const override
	{
		for (auto& shape : picture)
		{
			shape.Draw(canvas);
		}
	}
};
