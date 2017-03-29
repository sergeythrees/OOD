#include "stdafx.h"
#include "../DocumentEditor/ChangeStringCommand.h"

using namespace std;

struct changeStringFixture
{
	changeStringFixture()
		:sourceString("source"),
		newString("new"),
		command(sourceString, newString)
	{}
	string sourceString;
	string newString;
	CChangeStringCommand command;
};

BOOST_FIXTURE_TEST_SUITE(CChangeStringCommand_, changeStringFixture)

	BOOST_AUTO_TEST_CASE(can_execute_and_unexecute)
	{
		command.Execute();
		BOOST_CHECK_EQUAL(sourceString, newString);
		command.Unexecute();
		BOOST_CHECK_EQUAL(sourceString, "source");
	}
BOOST_AUTO_TEST_SUITE_END()