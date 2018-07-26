#include "stdafx.h"
#include "Designer.h"
#include "PictureDraft.h"
#include "IShapeFactory.h"
#include <iostream>

using namespace std;

CDesigner::CDesigner(IShapeFactory & factory)
	:m_factory(factory)
{
}


CDesigner::~CDesigner()
{
}

CPictureDraft CDesigner::CreateDraft(std::istream & inputData)
{
	CPictureDraft draft;
	string line;
	while (getline(inputData, line))
	{
		try
		{
			if (auto sh = m_factory.CreateShape(line))
			{
				draft.AddShape(std::move(sh));
			}
			else
			{
				std::cerr << "Shape description is incorrect\n";
			}
		}
		catch (std::exception& e)
		{
			std::cerr << "Error while creating shape: ";
			std::cerr << e.what();
			std::cerr << "\n";
		}
	}
	return draft;
}
