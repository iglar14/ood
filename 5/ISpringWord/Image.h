#pragma once
#include "IImage.h"
#include "IWorkCopy.h"

class CImage : public IImage
{
public:
	CImage(std::unique_ptr<IWorkCopy> wc);

	std::string GetPath()const override;

	// Ширина изображения в пикселях
	int GetWidth()const { return m_width; };
	// Высота изображения в пикселях
	int GetHeight()const { return m_height; }

	// Изменяет размер изображения
	void Resize(int width, int height) override;

private:
	std::unique_ptr<IWorkCopy> m_copy;
	int m_width = 0;
	int m_height = 0;
};