#include "stdafx.h"
#include "MockStorage.h"
#include "..\ISpringWord\Document.h"
#include "..\ISpringWord\WordException.h"

using namespace std;

struct Document_
{
	CDocument m_document;
//	IStorage* m_storage;

	Document_()
		: m_document(CreateStorage())
	{
	}

	std::unique_ptr<IStorage> CreateStorage()
	{
		auto storage = std::make_unique<MockStorage>();
		return storage;
	}
};

BOOST_FIXTURE_TEST_SUITE(CDocument_tests, Document_)

BOOST_AUTO_TEST_CASE(title_changes)
{
	const string NEW_TITLE = "new title";
	const string NEW_TITLE2 = "new title 2 ";

	BOOST_CHECK_EQUAL(m_document.GetTitle(), "");
	m_document.SetTitle(NEW_TITLE);
	BOOST_CHECK_EQUAL(m_document.GetTitle(), NEW_TITLE);

	m_document.SetTitle(NEW_TITLE2);
	BOOST_CHECK_EQUAL(m_document.GetTitle(), NEW_TITLE2);

	m_document.Undo();
	BOOST_CHECK_EQUAL(m_document.GetTitle(), NEW_TITLE);

	m_document.Undo();
	BOOST_CHECK_EQUAL(m_document.GetTitle(), "");

	m_document.Redo();
	BOOST_CHECK_EQUAL(m_document.GetTitle(), NEW_TITLE);
}

BOOST_AUTO_TEST_CASE(inserts_paragraph_to_the_end)
{
	const string PARA_1 = "paragraph 1";
	const string PARA_2 = "paragraph 2";

	auto p0 = m_document.InsertParagraph(PARA_1);
	BOOST_CHECK_EQUAL(m_document.GetItemsCount(), 1u);
	BOOST_CHECK_EQUAL(m_document.GetItem(0).GetParagraph(), p0);
	BOOST_CHECK_EQUAL(m_document.GetItem(0).GetParagraph()->GetText(), PARA_1);

	auto p1 = m_document.InsertParagraph(PARA_2);
	BOOST_CHECK_EQUAL(m_document.GetItemsCount(), 2u);
	BOOST_CHECK_EQUAL(m_document.GetItem(1).GetParagraph(), p1);
	BOOST_CHECK_EQUAL(m_document.GetItem(1).GetParagraph()->GetText(), PARA_2);

	m_document.Undo();
	BOOST_CHECK_EQUAL(m_document.GetItemsCount(), 1u);
	BOOST_CHECK_EQUAL(m_document.GetItem(0).GetParagraph(), p0);
	BOOST_CHECK_EQUAL(m_document.GetItem(0).GetParagraph()->GetText(), PARA_1);

	m_document.Redo();
	BOOST_CHECK_EQUAL(m_document.GetItemsCount(), 2u);
	BOOST_CHECK_EQUAL(m_document.GetItem(1).GetParagraph(), p1);
	BOOST_CHECK_EQUAL(m_document.GetItem(1).GetParagraph()->GetText(), PARA_2);

	m_document.Undo();
	m_document.Undo();
	BOOST_CHECK_EQUAL(m_document.GetItemsCount(), 0u);
}

BOOST_AUTO_TEST_CASE(inserts_paragraph_to_any_pos)
{
	const string PARA_1 = "paragraph 1";
	const string PARA_2 = "paragraph 2";
	const string PARA_3 = "paragraph 3";

	auto p0 = m_document.InsertParagraph(PARA_1);
	auto p1 = m_document.InsertParagraph(PARA_2);
	auto p2 = m_document.InsertParagraph(PARA_3);

	const string INS_PARA_1 = "insert 1";
	const string INS_PARA_2 = "insert 2";
	const string INS_PARA_3 = "insert 3";

	m_document.InsertParagraph(INS_PARA_1, 0);
	m_document.InsertParagraph(INS_PARA_2, 0);
	m_document.InsertParagraph(INS_PARA_3, 3);

	BOOST_CHECK_EQUAL(m_document.GetItemsCount(), 6u);
	BOOST_CHECK_EQUAL(m_document.GetItem(0).GetParagraph()->GetText(), INS_PARA_2);
	BOOST_CHECK_EQUAL(m_document.GetItem(1).GetParagraph()->GetText(), INS_PARA_1);
	BOOST_CHECK_EQUAL(m_document.GetItem(2).GetParagraph()->GetText(), PARA_1);
	BOOST_CHECK_EQUAL(m_document.GetItem(3).GetParagraph()->GetText(), INS_PARA_3);
	BOOST_CHECK_EQUAL(m_document.GetItem(4).GetParagraph()->GetText(), PARA_2);
	BOOST_CHECK_EQUAL(m_document.GetItem(5).GetParagraph()->GetText(), PARA_3);

	m_document.Undo();
	BOOST_CHECK_EQUAL(m_document.GetItem(2).GetParagraph()->GetText(), PARA_1);
	BOOST_CHECK_EQUAL(m_document.GetItem(3).GetParagraph()->GetText(), PARA_2);
	BOOST_CHECK_EQUAL(m_document.GetItem(4).GetParagraph()->GetText(), PARA_3);
	m_document.Undo();

	BOOST_CHECK_EQUAL(m_document.GetItemsCount(), 4u);
	BOOST_CHECK_NO_THROW(m_document.InsertParagraph(INS_PARA_3, 4));
	BOOST_CHECK_THROW(m_document.InsertParagraph(INS_PARA_3, 6), CWordException);
}

BOOST_AUTO_TEST_CASE(inserts_image)
{
	const string PATH_1 = "c:\\temp\\1.png";
	const string PATH_2 = "c:\\somewhere\\2.png";

	auto i1 = m_document.InsertImage(PATH_1, 800, 600);
	auto i0 = m_document.InsertImage(PATH_2, 640, 480, 0);

	BOOST_CHECK_EQUAL(m_document.GetItemsCount(), 2u);
	BOOST_CHECK_EQUAL(m_document.GetItem(0).GetImage(), i0);
	BOOST_CHECK_EQUAL(i0->GetPath(), PATH_2);
	BOOST_CHECK_EQUAL(i0->GetWidth(), 640);
	BOOST_CHECK_EQUAL(i0->GetHeight(), 480);
	BOOST_CHECK_EQUAL(m_document.GetItem(1).GetImage(), i1);
	BOOST_CHECK_EQUAL(i1->GetPath(), PATH_1);
	BOOST_CHECK_EQUAL(i1->GetWidth(), 800);
	BOOST_CHECK_EQUAL(i1->GetHeight(), 600);

	BOOST_CHECK_THROW(m_document.InsertImage(PATH_2, 1000, 500, 3), CWordException);
}

BOOST_AUTO_TEST_CASE(new_document_has_no_history)
{
	BOOST_CHECK(!m_document.CanUndo());
	BOOST_CHECK(!m_document.CanRedo());
}
BOOST_AUTO_TEST_SUITE_END()

struct Document_with_items_ : Document_
{
	const string PARA_1 = "paragraph 1";
	const string PARA_2 = "paragraph 2";
	const string PARA_3 = "paragraph 3";
	const string PATH_1 = "c:\\temp\\1.png";
	const string PATH_2 = "c:\\somewhere\\2.png";

	Document_with_items_()
	{
		m_document.InsertParagraph(PARA_1);
		m_document.InsertImage(PATH_1, 800, 600);
		m_document.InsertParagraph(PARA_2);
		m_document.InsertParagraph(PARA_3);
		m_document.InsertImage(PATH_2, 640, 480);
	}
};

BOOST_FIXTURE_TEST_SUITE(CDocument_manages_items, Document_with_items_)
BOOST_AUTO_TEST_CASE(deletes)
{
	BOOST_CHECK_EQUAL(m_document.GetItemsCount(), 5u);
	m_document.DeleteItem(0);
	BOOST_CHECK_EQUAL(m_document.GetItemsCount(), 4u);
	BOOST_CHECK_EQUAL(m_document.GetItem(0).GetImage()->GetPath(), PATH_1);
	BOOST_CHECK_EQUAL(m_document.GetItem(1).GetParagraph()->GetText(), PARA_2);
	BOOST_CHECK_EQUAL(m_document.GetItem(2).GetParagraph()->GetText(), PARA_3);
	BOOST_CHECK_EQUAL(m_document.GetItem(3).GetImage()->GetPath(), PATH_2);
	
	m_document.Undo();
	BOOST_CHECK_EQUAL(m_document.GetItemsCount(), 5u);
	BOOST_CHECK_EQUAL(m_document.GetItem(0).GetParagraph()->GetText(), PARA_1);
	BOOST_CHECK_EQUAL(m_document.GetItem(1).GetImage()->GetPath(), PATH_1);
	BOOST_CHECK_EQUAL(m_document.GetItem(2).GetParagraph()->GetText(), PARA_2);
	BOOST_CHECK_EQUAL(m_document.GetItem(3).GetParagraph()->GetText(), PARA_3);
	BOOST_CHECK_EQUAL(m_document.GetItem(4).GetImage()->GetPath(), PATH_2);

	m_document.DeleteItem(4);
	BOOST_CHECK_EQUAL(m_document.GetItemsCount(), 4u);
	BOOST_CHECK_EQUAL(m_document.GetItem(0).GetParagraph()->GetText(), PARA_1);
	BOOST_CHECK_EQUAL(m_document.GetItem(1).GetImage()->GetPath(), PATH_1);
	BOOST_CHECK_EQUAL(m_document.GetItem(2).GetParagraph()->GetText(), PARA_2);
	BOOST_CHECK_EQUAL(m_document.GetItem(3).GetParagraph()->GetText(), PARA_3);

	BOOST_CHECK_THROW(m_document.DeleteItem(4), CWordException);
}
BOOST_AUTO_TEST_CASE(resizes_images)
{
	m_document.ResizeImage(1, 900, 300);
	BOOST_CHECK_EQUAL(m_document.GetItem(1).GetImage()->GetPath(), PATH_1);
	BOOST_CHECK_EQUAL(m_document.GetItem(1).GetImage()->GetWidth(), 900);
	BOOST_CHECK_EQUAL(m_document.GetItem(1).GetImage()->GetHeight(), 300);

	m_document.Undo();
	BOOST_CHECK_EQUAL(m_document.GetItem(1).GetImage()->GetWidth(), 800);
	BOOST_CHECK_EQUAL(m_document.GetItem(1).GetImage()->GetHeight(), 600);

	BOOST_CHECK_THROW(m_document.ResizeImage(0, 800, 500), CWordException);
	BOOST_CHECK_THROW(m_document.ResizeImage(1, 0, 500), CWordException);
	BOOST_CHECK_THROW(m_document.ResizeImage(5, 800, 500), CWordException);
}
BOOST_AUTO_TEST_CASE(replaces_text)
{
	const string NEW_TEXT = "new text";
	m_document.ReplaceText(0, NEW_TEXT);
	BOOST_CHECK_EQUAL(m_document.GetItem(0).GetParagraph()->GetText(), NEW_TEXT);

	m_document.Undo();
	BOOST_CHECK_EQUAL(m_document.GetItem(0).GetParagraph()->GetText(), PARA_1);
	m_document.Redo();
	BOOST_CHECK_EQUAL(m_document.GetItem(0).GetParagraph()->GetText(), NEW_TEXT);

	BOOST_CHECK_THROW(m_document.ReplaceText(1, NEW_TEXT), CWordException);
	BOOST_CHECK_THROW(m_document.ReplaceText(5, NEW_TEXT), CWordException);
}

BOOST_AUTO_TEST_SUITE_END()
