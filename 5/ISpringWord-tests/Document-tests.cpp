#include "stdafx.h"
#include "..\ISpringWord\Document.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CDocument_tests)

BOOST_AUTO_TEST_CASE(title_changes)
{
	const string NEW_TITLE = "new title";
	const string NEW_TITLE2 = "new title 2 ";
	CDocument doc;

	BOOST_CHECK_EQUAL(doc.GetTitle(), "");
	doc.SetTitle(NEW_TITLE);
	BOOST_CHECK_EQUAL(doc.GetTitle(), NEW_TITLE);

	doc.SetTitle(NEW_TITLE2);
	BOOST_CHECK_EQUAL(doc.GetTitle(), NEW_TITLE2);

	doc.Undo();
	BOOST_CHECK_EQUAL(doc.GetTitle(), NEW_TITLE);

	doc.Undo();
	BOOST_CHECK_EQUAL(doc.GetTitle(), "");

	doc.Redo();
	BOOST_CHECK_EQUAL(doc.GetTitle(), NEW_TITLE);
}

BOOST_AUTO_TEST_CASE(inserts_paragraph_to_the_end)
{
	const string PARA_1 = "paragraph 1";
	const string PARA_2 = "paragraph 2";
	CDocument doc;

	auto p0 = doc.InsertParagraph(PARA_1);
	BOOST_CHECK_EQUAL(doc.GetItemsCount(), 1u);
	BOOST_CHECK_EQUAL(doc.GetItem(0).GetParagraph(), p0);
	BOOST_CHECK_EQUAL(doc.GetItem(0).GetParagraph()->GetText(), PARA_1);

	auto p1 = doc.InsertParagraph(PARA_2);
	BOOST_CHECK_EQUAL(doc.GetItemsCount(), 2u);
	BOOST_CHECK_EQUAL(doc.GetItem(1).GetParagraph(), p1);
	BOOST_CHECK_EQUAL(doc.GetItem(1).GetParagraph()->GetText(), PARA_2);
}

BOOST_AUTO_TEST_CASE(new_document_has_no_history)
{
	CDocument doc;
	BOOST_CHECK(!doc.CanUndo());
	BOOST_CHECK(!doc.CanRedo());
}

BOOST_AUTO_TEST_SUITE_END()
