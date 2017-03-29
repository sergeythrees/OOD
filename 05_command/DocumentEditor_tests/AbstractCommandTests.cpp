#include "stdafx.h"
#include "AbstractCommandMock.h"

using namespace std;
struct commandFixture
{
	commandFixture()
	{
		commands.push_back(make_shared<CommandMock>());
	}
	commandsArray commands;
};
BOOST_FIXTURE_TEST_SUITE(CAbstractCommand_, commandFixture)
	BOOST_AUTO_TEST_CASE(can_execute_and_unexecute_with_ICommand_interface)
	{
		BOOST_CHECK(!static_cast<CommandMock*>(commands[0].get())->IsExecuted());
		commands[0]->Execute();
		BOOST_CHECK(static_cast<CommandMock*>(commands[0].get())->IsExecuted());
		commands[0]->Unexecute();
		BOOST_CHECK(!static_cast<CommandMock*>(commands[0].get())->IsExecuted());
	}


BOOST_AUTO_TEST_SUITE_END()

