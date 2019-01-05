#pragma once
#include "ICommand_fwd.h"

class IImmutableImage
{
public:
	// ���������� ���� ������������ �������� ���������
	virtual std::string GetPath()const = 0;

	// ������ ����������� � ��������
	virtual int GetWidth()const = 0;
	// ������ ����������� � ��������
	virtual int GetHeight()const = 0;

	virtual ~IImmutableImage() = default;
};

class IImage : public IImmutableImage
{
public:
	// �������� ������ �����������
	virtual ICommandPtr Resize(int width, int height) = 0;
};
