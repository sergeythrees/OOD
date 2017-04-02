

#include "stdafx.h"
#include "../DocumentEditor/History.h"
#include "../DocumentEditor/AbstractCommand.h"

using namespace std;

typedef std::map<int, bool> commandsArray;

class CommandMock : public CAbstractCommand
{
public:
	CommandMock(commandsArray& commands, int id) 
		:m_commands(commands),
		m_id(id)
	{
		commands.emplace(id, false);
	}
	~CommandMock()
	{
		if (!m_commands.empty())
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
	int m_id;
	commandsArray& m_commands;
};

struct historyFixture
{
	historyFixture()
		:history(),
		commands()
	{}

	CHistory history;
	commandsArray commands;
}; 

BOOST_FIXTURE_TEST_SUITE(CHistory_, historyFixture)
	BOOST_AUTO_TEST_SUITE(after_construction)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK(!history.CanUndo());
			BOOST_CHECK(!history.CanRedo());
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_CASE(can_add_and_execute_commands)
	{
		history.AddAndExecuteCommand(make_unique<CommandMock>(commands, 0));
		history.AddAndExecuteCommand(make_unique<CommandMock>(commands, 2));
		BOOST_CHECK_EQUAL(commands.size(), 2);
	}
	BOOST_AUTO_TEST_CASE(can_undo_and_redo_commands)
	{
		history.AddAndExecuteCommand(make_unique<CommandMock>(commands, 0));
		history.AddAndExecuteCommand(make_unique<CommandMock>(commands, 2));
		history.Undo();
		BOOST_CHECK(!commands[2]);
		history.Undo();
		BOOST_CHECK(!commands[0]);
		BOOST_CHECK(!history.CanUndo());
		history.Redo();
		BOOST_CHECK(commands[0]);
		history.Redo();
		BOOST_CHECK(commands[2]);
		BOOST_CHECK(!history.CanRedo());
	}
	BOOST_AUTO_TEST_CASE(should_erase_commands_if_history_is_changed)
	{
		history.AddAndExecuteCommand(make_unique<CommandMock>(commands, 0));
		history.AddAndExecuteCommand(make_unique<CommandMock>(commands, 2));
		history.Undo();
		history.AddAndExecuteCommand(make_unique<CommandMock>(commands, 3));
		BOOST_CHECK_EQUAL(commands.size(), 2);
		BOOST_CHECK(commands[3]); 
		BOOST_CHECK(commands[0]);
	}
	BOOST_AUTO_TEST_CASE(should_erase_commands_if_capacity_is_filled)
	{
		for (int i=0; i < 15;++i)
			history.AddAndExecuteCommand(make_unique<CommandMock>(commands, i));
		BOOST_CHECK_EQUAL(commands.size(), 10);
		auto it = commands.begin();
		for (int i = 5; i < 15; ++i, ++it)
			BOOST_CHECK_EQUAL(it->first, i);
	}
BOOST_AUTO_TEST_SUITE_END()
	