#pragma once

#include "ICommand_fwd.h"

class CHistory
{
public:
	CHistory();
	~CHistory();

	CHistory(const CHistory&) = delete;
	CHistory(CHistory&&) = default;

	CHistory& operator=(const CHistory&) = delete;
	CHistory& operator=(CHistory&&) = default;

	bool CanUndo()const;	
	void Undo();
	bool CanRedo()const;
	void Redo();
	void AddAndExecuteCommand(ICommandPtr && command);
private:
	std::deque<ICommandPtr> m_commands;
	size_t m_nextCommandIndex = 0;
};

