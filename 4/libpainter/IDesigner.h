#pragma once
#include "PictureDraft.h"

class IDesigner
{
public:
	virtual ~IDesigner() = default;

	CPictureDraft CreateDraft(std::istream & inputData);
};
