#include "stdafx.h"
#include "../ISpringWord/History.h"
#include "../ISpringWord/Paragraph.h"
#include "../ISpringWord/WordException.h"

using namespace std;
const string PARA_1 = "paragraph 1";

struct Paragraph_
{
	CHistory history;
	std::shared_ptr<IParagraph> para = std::make_shared<CParagraph>(history, PARA_1);
};

BOOST_FIXTURE_TEST_SUITE(Paragraph, Paragraph_)

BOOST_AUTO_TEST_CASE(replaces_text)
{
	const string NEW_TEXT = "new text";
	para->SetText(NEW_TEXT);
	BOOST_CHECK_EQUAL(para->GetText(), NEW_TEXT);

	BOOST_CHECK(history.CanUndo());
	BOOST_CHECK(!history.CanRedo());

	history.Undo();
	BOOST_CHECK_EQUAL(para->GetText(), PARA_1);

	BOOST_CHECK(!history.CanUndo());
	BOOST_CHECK(history.CanRedo());

	history.Redo();
	BOOST_CHECK_EQUAL(para->GetText(), NEW_TEXT);

	BOOST_CHECK(history.CanUndo());
	BOOST_CHECK(!history.CanRedo());
}
BOOST_AUTO_TEST_SUITE_END()