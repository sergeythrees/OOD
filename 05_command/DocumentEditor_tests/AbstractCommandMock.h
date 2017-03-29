#pragma once
#include "stdafx.h"
#include "../DocumentEditor/AbstractCommand.h"

typedef std::vector<std::shared_ptr<ICommand>> commandsArray;

class CommandMock : public CAbstractCommand
{
public:
	CommandMock()
		:m_isExecuted(false) {}

	bool IsExecuted() const
	{
		return m_isExecuted;
	}
protected:
	void DoExecute() override
	{
		m_isExecuted = true;
	}
	void DoUnexecute() override
	{
		m_isExecuted = false;
	}
private:
	bool m_isExecuted;
};