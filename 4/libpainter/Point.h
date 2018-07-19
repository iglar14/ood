#pragma once

template <class T>
struct PointT
{
	T x, y;
	bool operator==(const PointT<T>& p2)
	{
		return std::tie(x, y) == std::tie(p2.x, p2.y);
	}
};

using PointI = PointT<int>;
using PointF = PointT<float>;

PointF MakePointF(const PointI& p)
{
	return{ static_cast<float>(p.x), static_cast<float>(p.y) };
}

template <class T>
struct SizeT
{
	T width, height;
};

using SizeI = SizeT<int>;
using SizeF = SizeT<float>;
