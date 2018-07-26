#include "stdafx.h"
#include "../libpainter/ShapeFactory.h"
#include "../libpainter/Rectangle.h"
#include "../libpainter/Triangle.h"
#include "../libpainter/Ellipse.h"
#include "../libpainter/RegularPolygon.h"

struct Factory_
{
	ShapeFactory factory;
};

BOOST_FIXTURE_TEST_SUITE(Factory, Factory_)

BOOST_AUTO_TEST_CASE(creates_rectangle)
{
	CShapePtr sh = factory.CreateShape("rectangle green -10 +20 30 40");
	BOOST_REQUIRE(sh);
	BOOST_CHECK(sh->GetColor() == Color::Green);
	std::shared_ptr<CRectangle> shRect = std::dynamic_pointer_cast<CRectangle>(sh);
	BOOST_CHECK(shRect);
	BOOST_CHECK(shRect->GetLeftTop() == (PointI{ -10, 20 }));
	BOOST_CHECK(shRect->GetRightBottom() == (PointI{ 30, 40 }));
}

BOOST_AUTO_TEST_CASE(throws_on_incorrect_color)
{
	BOOST_CHECK_THROW(factory.CreateShape("rectangle greooen 10 20 30 40"), IShapeFactory::Exception);
}

BOOST_AUTO_TEST_CASE(creates_triangle)
{
	CShapePtr sh = factory.CreateShape("triangle pink 10 20 30 40 -10 50");
	BOOST_REQUIRE(sh);
	BOOST_CHECK(sh->GetColor() == Color::Pink);
	std::shared_ptr<CTriangle> shTr = std::dynamic_pointer_cast<CTriangle>(sh);
	BOOST_CHECK(shTr);
	BOOST_CHECK(shTr->GetVertex1() == (PointI{ 10, 20 }));
	BOOST_CHECK(shTr->GetVertex2() == (PointI{ 30, 40 }));
	BOOST_CHECK(shTr->GetVertex3() == (PointI{ -10, 50 }));
}

BOOST_AUTO_TEST_CASE(creates_ellipse)
{
	CShapePtr sh = factory.CreateShape("ellipse red 10 20 30 40");
	BOOST_REQUIRE(sh);
	BOOST_CHECK(sh->GetColor() == Color::Red);
	std::shared_ptr<CEllipse> shEl = std::dynamic_pointer_cast<CEllipse>(sh);
	BOOST_CHECK(shEl);
	BOOST_CHECK(shEl->GetCenter() == (PointI{ 10, 20 }));
	BOOST_CHECK_EQUAL(shEl->GetHorizontalRadius(), 30);
	BOOST_CHECK_EQUAL(shEl->GetVerticalRadius(), 40);
}

BOOST_AUTO_TEST_CASE(creates_regular_polygon)
{
	CShapePtr sh = factory.CreateShape("polygon blue 10 20 30 7");
	BOOST_REQUIRE(sh);
	BOOST_CHECK(sh->GetColor() == Color::Blue);
	std::shared_ptr<CRegularPolygon> shPol = std::dynamic_pointer_cast<CRegularPolygon>(sh);
	BOOST_CHECK(shPol);
	BOOST_CHECK(shPol->GetCenter() == (PointI{ 10, 20 }));
	BOOST_CHECK_EQUAL(shPol->GetRadius(), 30);
	BOOST_CHECK_EQUAL(shPol->GetVertexCount(), 7);
}

BOOST_AUTO_TEST_SUITE_END()