#pragma once
#include "IImage.h"
#include "IWorkCopy.h"

class CImage : public IImage
{
public:
	CImage(const WorkCopyFactory& wcFac);

	std::string GetPath()const override;
	void SetPath(const std::string& path);

	// ������ ����������� � ��������
	int GetWidth()const { return m_width; };
	// ������ ����������� � ��������
	int GetHeight()const { return m_height; }

	// �������� ������ �����������
	void Resize(int width, int height) override;

private:
	WorkCopyFactory m_wcFac;
	std::unique_ptr<IWorkCopy> m_copy;
	int m_width = 0;
	int m_height = 0;
};