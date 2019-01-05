#include "stdafx.h"
#include "MockStorage.h"
#include "../ISpringWord/ICommand.h"
#include "../ISpringWord/Image.h"
#include "../ISpringWord/WordException.h"

BOOST_AUTO_TEST_CASE(image_sizes)
{
	MockStorage storage;
	auto image = CImage::Create(storage.AddFile(L"image->jpg"), 400, 300);
	image->Resize(800, 600)->Execute();
	BOOST_CHECK_EQUAL(image->GetWidth(), 800);
	BOOST_CHECK_EQUAL(image->GetHeight(), 600);
	image->Resize(1, 1)->Execute();
	BOOST_CHECK_EQUAL(image->GetWidth(), 1);
	BOOST_CHECK_EQUAL(image->GetHeight(), 1);
	image->Resize(10000, 10000)->Execute();
	BOOST_CHECK_EQUAL(image->GetWidth(), 10000);
	BOOST_CHECK_EQUAL(image->GetHeight(), 10000);

	BOOST_CHECK_THROW(image->Resize(0, 200)->Execute(), CWordException);
	BOOST_CHECK_THROW(image->Resize(200, 0)->Execute(), CWordException);
	BOOST_CHECK_THROW(image->Resize(10001, 200)->Execute(), CWordException);
	BOOST_CHECK_THROW(image->Resize(200, 10001)->Execute(), CWordException);
}
