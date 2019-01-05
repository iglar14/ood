#pragma once
#include "AbstractCommand.h"

class CFunctionalCommand : public CAbstractCommand
{
public:
	using Functor = std::function<void()>;

	CFunctionalCommand(const Functor& executor, const Functor& unexecutor)
		: m_executor(executor)
		, m_unexecutor(unexecutor)
	{
	}

	void DoExecute() final { m_executor(); }
	void DoUnexecute() final { m_unexecutor(); }
private:
	Functor m_executor, m_unexecutor;
};