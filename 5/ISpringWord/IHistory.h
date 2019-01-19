#pragma once
#include "ICommandExecutor.h"

struct IHistory : ICommandExecutor
{
	virtual ~IHistory() = default;

	virtual bool CanUndo()const = 0;
	virtual void Undo() = 0;
	virtual bool CanRedo()const = 0;
	virtual void Redo() = 0;
};

