#include "stdafx.h"
#include "MockStorage.h"
#include "../ISpringWord/History.h"
#include "../ISpringWord/Image.h"
#include "../ISpringWord/WordException.h"

using namespace std;

const string PATH_1 = "c:\\temp\\1.png";

struct Image_
{
	MockStorage storage;
	CHistory history;
	std::shared_ptr<CImage> image = CImage::Create(history, storage.AddFile(PATH_1), 400, 300);
};

BOOST_FIXTURE_TEST_SUITE(Image, Image_)

BOOST_AUTO_TEST_CASE(image_sizes)
{
	image->Resize(800, 600);
	BOOST_CHECK_EQUAL(image->GetWidth(), 800);
	BOOST_CHECK_EQUAL(image->GetHeight(), 600);
	image->Resize(1, 1);
	BOOST_CHECK_EQUAL(image->GetWidth(), 1);
	BOOST_CHECK_EQUAL(image->GetHeight(), 1);
	image->Resize(10000, 10000);
	BOOST_CHECK_EQUAL(image->GetWidth(), 10000);
	BOOST_CHECK_EQUAL(image->GetHeight(), 10000);

	BOOST_CHECK_THROW(image->Resize(0, 200), CWordException);
	BOOST_CHECK_THROW(image->Resize(200, 0), CWordException);
	BOOST_CHECK_THROW(image->Resize(10001, 200), CWordException);
	BOOST_CHECK_THROW(image->Resize(200, 10001), CWordException);

	BOOST_CHECK_THROW(CImage::Create(history, storage.AddFile(PATH_1), 0, 300), CWordException);
}

BOOST_AUTO_TEST_CASE(undo_redo_resize)
{
	image->Resize(900, 500);
	BOOST_CHECK_EQUAL(image->GetPath(), PATH_1);
	BOOST_CHECK_EQUAL(image->GetWidth(), 900);
	BOOST_CHECK_EQUAL(image->GetHeight(), 500);

	BOOST_CHECK(history.CanUndo());
	BOOST_CHECK(!history.CanRedo());
	history.Undo();
	BOOST_CHECK_EQUAL(image->GetWidth(), 400);
	BOOST_CHECK_EQUAL(image->GetHeight(), 300);

	BOOST_CHECK(!history.CanUndo());
	BOOST_CHECK(history.CanRedo());

	history.Redo();
	BOOST_CHECK_EQUAL(image->GetWidth(), 900);
	BOOST_CHECK_EQUAL(image->GetHeight(), 500);

	BOOST_CHECK(history.CanUndo());
	BOOST_CHECK(!history.CanRedo());
}

BOOST_AUTO_TEST_SUITE_END()