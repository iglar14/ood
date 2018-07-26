#pragma once
#include "IPainter.h"
#include "PictureDraft.h"
#include "ICanvas.h"

class CPainter : public IPainter
{
public:
//	CPainter()
// 	virtual ~IPainter() = default;

	void DrawPicture(const CPictureDraft& draft, ICanvas& canvas) const override;
};