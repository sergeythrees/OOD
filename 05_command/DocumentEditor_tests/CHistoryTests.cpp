

#include "stdafx.h"
#include "../DocumentEditor/History.h"
#include "AbstractCommandMock.h"

using namespace std;

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
		//history.AddAndExecuteCommand(make_unique<CommandMock>(commands, 0));
		/*BOOST_CHECK(history.CanUndo());
		BOOST_CHECK(!history.CanRedo());*/
	}
BOOST_AUTO_TEST_SUITE_END()