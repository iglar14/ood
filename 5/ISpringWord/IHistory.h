#pragma once
#include "ICommand_fwd.h"

struct IHistory
{
	virtual ~IHistory() = default;

	virtual bool CanUndo()const = 0;
	virtual void Undo() = 0;
	virtual bool CanRedo()const = 0;
	virtual void Redo() = 0;
	virtual void AddAndExecuteCommand(ICommandPtr && command) = 0;
};

