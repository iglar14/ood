#include "stdafx.h"
#include "../ISpringWord/History.h"
#include "../ISpringWord/FunctionalCommand.h"

struct History_
{
	CHistory m_history;
};

BOOST_FIXTURE_TEST_SUITE(History, History_)

BOOST_AUTO_TEST_CASE(is_empty)
{
	BOOST_CHECK(!m_history.CanUndo());
	BOOST_CHECK(!m_history.CanRedo());
}

static constexpr int HISTORY_LIMIT = 10;
static constexpr int START_VALUE = 420;

struct HistoryLimits_ : History_
{
	int value = START_VALUE;

	void ExecuteCommand()
	{
		m_history.AddAndExecuteCommand(std::make_unique<CFunctionalCommand>(
			[&]() { ++value; }, 
			[&]() { --value; }));
	}
};
BOOST_FIXTURE_TEST_CASE(undo_redo, HistoryLimits_)
{
	ExecuteCommand();

	BOOST_CHECK_EQUAL(value, START_VALUE + 1);
	BOOST_CHECK(m_history.CanUndo());
	BOOST_CHECK(!m_history.CanRedo());

	m_history.Undo();
	BOOST_CHECK_EQUAL(value, START_VALUE);
	BOOST_CHECK(!m_history.CanUndo());
	BOOST_CHECK(m_history.CanRedo());

	m_history.Undo();
	BOOST_CHECK_EQUAL(value, START_VALUE);
	BOOST_CHECK(!m_history.CanUndo());
	BOOST_CHECK(m_history.CanRedo());

	m_history.Redo();
	BOOST_CHECK_EQUAL(value, START_VALUE + 1);
	BOOST_CHECK(m_history.CanUndo());
	BOOST_CHECK(!m_history.CanRedo());

	m_history.Redo();
	BOOST_CHECK_EQUAL(value, START_VALUE + 1);
	BOOST_CHECK(m_history.CanUndo());
	BOOST_CHECK(!m_history.CanRedo());

	ExecuteCommand();
	BOOST_CHECK_EQUAL(value, START_VALUE + 2);
	BOOST_CHECK(m_history.CanUndo());
	BOOST_CHECK(!m_history.CanRedo());

	m_history.Undo();
	BOOST_CHECK_EQUAL(value, START_VALUE + 1);
	BOOST_CHECK(m_history.CanUndo());
	BOOST_CHECK(m_history.CanRedo());

	m_history.Undo();
	BOOST_CHECK_EQUAL(value, START_VALUE);
	BOOST_CHECK(!m_history.CanUndo());
	BOOST_CHECK(m_history.CanRedo());
}

BOOST_FIXTURE_TEST_CASE(history_limit, HistoryLimits_)
{
	for (int i = 0; i < 20; ++i)
	{
		ExecuteCommand();
	}

	BOOST_CHECK_EQUAL(value, START_VALUE + 20);
	BOOST_CHECK(m_history.CanUndo());
	BOOST_CHECK(!m_history.CanRedo());

	while (m_history.CanUndo())
	{
		m_history.Undo();
	}
	BOOST_CHECK_EQUAL(value, START_VALUE + HISTORY_LIMIT);
	BOOST_CHECK(!m_history.CanUndo());
	BOOST_CHECK(m_history.CanRedo());

	while (m_history.CanRedo())
	{
		m_history.Redo();
	}

	BOOST_CHECK_EQUAL(value, START_VALUE + 20);
	BOOST_CHECK(m_history.CanUndo());
	BOOST_CHECK(!m_history.CanRedo());
}
BOOST_AUTO_TEST_SUITE_END()
