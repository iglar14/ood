#include "stdafx.h"
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

	void Draw(ICanvas&) override {}
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
