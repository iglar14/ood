#pragma once

class CPictureDraft;
class ICanvas;

class IPainter
{
public:
	virtual ~IPainter() = default;

	virtual void DrawPicture(const CPictureDraft& draft, ICanvas& canvas) const = 0;
};