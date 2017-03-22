#pragma once
#include "../libpainter/ICanvas.h"
#include "../libpainter/PictureDraft.h"

class IPainter
{
public:
	virtual ~IPainter() = default;
	virtual void DrawPicture(const CPictureDraft& picture, ICanvas& canvas) const = 0;
};