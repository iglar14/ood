#include "stdafx.h"
#include "../libpainter/ICanvas.h"
#include "../libpainter/Shape.h"
#include "../libpainter/Rectangle.h"
#include "../libpainter/Triangle.h"
#include "../libpainter/Ellipse.h"
#include "../libpainter/RegularPolygon.h"

class ICanvas;

class MockShape : public CShape
{
public:
	using CShape::CShape;

	void Draw(ICanvas&) const override {}
};

BOOST_AUTO_TEST_CASE(Shape_has_color)
{
	MockShape sh1(Color::Red);
	BOOST_CHECK(sh1.GetColor() == Color::Red);

	MockShape sh2(Color::Blue);
	BOOST_CHECK(sh2.GetColor() == Color::Blue);
}

BOOST_AUTO_TEST_CASE(Rectangle_initialization)
{
	CRectangle rect(Color::Red, PointI{ 10, 30 }, PointI{ 50, 40 });
	BOOST_CHECK(rect.GetColor() == Color::Red);
	BOOST_CHECK(rect.GetLeftTop() == (PointI{ 10, 30 }));
	BOOST_CHECK(rect.GetRightBottom() == (PointI{ 50, 40 }));
}

BOOST_AUTO_TEST_CASE(Triangle_initialization)
{
	CTriangle tr(Color::Red, PointI{ 10, 30 }, PointI{ 50, 40 }, PointI{ 20, 50 });
	BOOST_CHECK(tr.GetColor() == Color::Red);
	BOOST_CHECK(tr.GetVertex1() == (PointI{ 10, 30 }));
	BOOST_CHECK(tr.GetVertex2() == (PointI{ 50, 40 }));
	BOOST_CHECK(tr.GetVertex3() == (PointI{ 20, 50 }));
}

BOOST_AUTO_TEST_CASE(Ellipse_initialization)
{
	CEllipse ellipse(Color::Red, PointI{ 10, 30 }, 40, 50);
	BOOST_CHECK(ellipse.GetColor() == Color::Red);
	BOOST_CHECK(ellipse.GetCenter() == (PointI{ 10, 30 }));
	BOOST_CHECK_EQUAL(ellipse.GetHorizontalRadius(), 40);
	BOOST_CHECK_EQUAL(ellipse.GetVerticalRadius(), 50);
}

BOOST_AUTO_TEST_CASE(RegularPolygon_initialization)
{
	CRegularPolygon poly(Color::Green, PointI{ 10, 30 }, 40, 5);
	BOOST_CHECK(poly.GetColor() == Color::Green);
	BOOST_CHECK(poly.GetCenter() == (PointI{ 10, 30 }));
	BOOST_CHECK_EQUAL(poly.GetRadius(), 40);
	BOOST_CHECK_EQUAL(poly.GetVertexCount(), 5);
}

BOOST_AUTO_TEST_CASE(RegularPolygon_throws_if_invalid_vertex_count)
{
	CRegularPolygon polyNorm(Color::Green, PointI{ 10, 30 }, 40, 3);
	BOOST_REQUIRE_THROW(CRegularPolygon(Color::Green, PointI{ 10, 30 }, 40, 2), CRegularPolygon::InvalidVertexCount);
}

struct MockCanvas : public ICanvas
{
	struct EllipseRec
	{
		PointF center;
		float rx;
		float ry;
	};
	void SetPenColor(Color color)
	{
		m_colors.push_back(color);
	}
	void DrawLine(const PointF& p1, const PointF& p2)
	{
		m_lines.emplace_back(p1, p2);
	}
	void DrawEllipse(const PointF& center, float rx, float ry)
	{
		m_ellipses.emplace_back(EllipseRec{ center, rx, ry });
	}

	std::vector<Color> m_colors;
	std::vector<std::pair<PointF, PointF>> m_lines;
	std::vector<EllipseRec> m_ellipses;
};
struct Canvas_
{
	void CheckColor(Color c)
	{
		BOOST_CHECK_EQUAL(canvas.m_colors.size(), 1u);
		BOOST_CHECK(c == canvas.m_colors[0]);
	}
	void CheckPoint(const PointF& p1, const PointF& p2)
	{
		BOOST_CHECK_CLOSE(p1.x, p2.x, 0.001f);
		BOOST_CHECK_CLOSE(p1.y, p2.y, 0.001f);
	}
	void CheckLine(size_t index, const PointF& p1, const PointF& p2)
	{
		CheckPoint(canvas.m_lines[index].first, p1);
		CheckPoint(canvas.m_lines[index].second, p2);
	}
	MockCanvas canvas;
};

BOOST_FIXTURE_TEST_SUITE(Drawing_on_canvas, Canvas_)

BOOST_AUTO_TEST_CASE(Rectangle)
{
	CRectangle rect(Color::Red, PointI{ 10, 30 }, PointI{ 50, 40 });
	rect.Draw(canvas);
	CheckColor(rect.GetColor());

	BOOST_CHECK_EQUAL(canvas.m_lines.size(), 4u);
	CheckLine(0, PointF{ 10.f, 30.f }, PointF{ 50.f, 30.f });
	CheckLine(1, PointF{ 50.f, 30.f }, PointF{ 50.f, 40.f });
	CheckLine(2, PointF{ 50.f, 40.f }, PointF{ 10.f, 40.f });
	CheckLine(3, PointF{ 10.f, 40.f }, PointF{ 10.f, 30.f });
}

BOOST_AUTO_TEST_CASE(Ellipse)
{
	CEllipse ellipse(Color::Red, PointI{ 10, 30 }, 40, 50);
	ellipse.Draw(canvas);
	CheckColor(ellipse.GetColor());

	BOOST_CHECK_EQUAL(canvas.m_ellipses.size(), 1u);
	auto canvasEll = canvas.m_ellipses[0];
	BOOST_CHECK(canvasEll.center == (PointF{ 10.f, 30.f }));
	BOOST_CHECK(canvasEll.rx == 40.f);
	BOOST_CHECK(canvasEll.ry == 50.f);
}

BOOST_AUTO_TEST_CASE(Triangle)
{
	CTriangle tr(Color::Red, PointI{ 10, 30 }, PointI{ 50, 40 }, PointI{ 20, 50 });
	tr.Draw(canvas);
	CheckColor(tr.GetColor());
	BOOST_CHECK_EQUAL(canvas.m_lines.size(), 3u);
	CheckLine(0, PointF{ 10.f, 30.f }, PointF{ 50.f, 40.f });
	CheckLine(1, PointF{ 50.f, 40.f }, PointF{ 20.f, 50.f });
	CheckLine(2, PointF{ 20.f, 50.f }, PointF{ 10.f, 30.f });
}

BOOST_AUTO_TEST_CASE(RegularPolygon)
{
	CRegularPolygon poly(Color::Green, PointI{ 10, 30 }, 40, 4);
	poly.Draw(canvas);

	CheckColor(poly.GetColor());
	BOOST_CHECK_EQUAL(canvas.m_lines.size(), 4u);
	CheckLine(0, PointF{ 10.f, 70.f }, PointF{ 50.f, 30.f });
	CheckLine(1, PointF{ 50.f, 30.f }, PointF{ 10.f, -10.f });
	CheckLine(2, PointF{ 10.f, -10.f }, PointF{ -30.f, 30.f });
	CheckLine(3, PointF{ -30.f, 30.f }, PointF{ 10.f, 70.f });
}

BOOST_AUTO_TEST_SUITE_END()