#include "stdafx.h"
#include "Painter.h"

void CPainter::DrawPicture(const CPictureDraft& draft, ICanvas& canvas) const
{
	for (CPictureDraft::ConstIterator iter = draft.begin(); iter != draft.end(); ++iter)
	{
		iter->Draw(canvas);
	}
}
