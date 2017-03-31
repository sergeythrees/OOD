#include "stdafx.h"
#include <map>
#include "../DocumentEditor/AbstractCommand.h"

typedef std::map<int, bool> commandsArray;

class CommandMock : public CAbstractCommand
{
public:
	CommandMock(commandsArray& commands, int id)
		:m_commands(commands),
		m_id(id),
		m_isExecuted(false) 
	{
		commands.emplace(id, false);
	}
	~CommandMock()
	{
		m_commands.erase(m_id);
	}
protected:
	void DoExecute() override
	{
		m_commands.at(m_id) = true;
	}
	void DoUnexecute() override
	{
		m_commands.at(m_id) = false;
	}
private:
	commandsArray& m_commands;
	int m_id;
	bool m_isExecuted;
};