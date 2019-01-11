#pragma once
#include "IHistory.h"
#include "IImage.h"
#include "IWorkCopy.h"

class CImage : public IImage, public std::enable_shared_from_this<CImage>
{
public:
	static std::shared_ptr<CImage> Create(IHistory& history, std::unique_ptr<IWorkCopy> wc, int width, int height);

	std::string GetPath()const override;

	// Ширина изображения в пикселях
	int GetWidth()const { return m_width; };
	// Высота изображения в пикселях
	int GetHeight()const { return m_height; }

	// Изменяет размер изображения
	void Resize(int width, int height) override;

private:
	CImage(IHistory& history, std::unique_ptr<IWorkCopy> wc);

	ICommandPtr ResizeImpl(int width, int height);

	class CResizeImageCommand;
	IHistory& m_history;
	std::unique_ptr<IWorkCopy> m_copy;
	int m_width = 0;
	int m_height = 0;
};