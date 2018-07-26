#pragma once
#include <iosfwd>
#include "IDesigner.h"

class CPictureDraft;

struct IShapeFactory;

class CDesigner : public IDesigner
{
public:
	CDesigner(IShapeFactory & factory);
	~CDesigner() override;
	CPictureDraft CreateDraft(std::istream & inputData);
private:
	IShapeFactory & m_factory;
};

