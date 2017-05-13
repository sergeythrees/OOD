#include "stdafx.h"
#include "TestFunctions.h"
#include "../NaiveGumBallMachine.h"


using namespace std;



BOOST_AUTO_TEST_SUITE(NaiveGumballMachine_)

	struct NaiveGumballMachineFixture : RedirectCout
	{
		NaiveGumballMachineFixture()
			:ballsCount(2),
			machine(ballsCount)
		{
		}

		unsigned ballsCount;
		naive::CGumballMachine machine;
	};
	BOOST_FIXTURE_TEST_SUITE(after_creation, NaiveGumballMachineFixture)
	
		BOOST_AUTO_TEST_CASE(has_preset_parameters)
		{
			BOOST_CHECK_EQUAL(machine.ToString(), R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: 2 gumballs
Machine is waiting for quarter
)");
		}
		BOOST_AUTO_TEST_CASE(has_not_quarter)
		{
			CheckFunctionOutput([&](){
				machine.EjectQuarter(); }, 
				"You haven't inserted a quarter\n");
		}
		BOOST_AUTO_TEST_CASE(can_insert_quarter)
		{
			CheckFunctionOutput([&]() {
				machine.InsertQuarter(); },
				"You inserted a quarter\n");
		}
		BOOST_AUTO_TEST_CASE(turn_crank_function_can_not_release_a_ball)
		{
			CheckFunctionOutput([&]() {
				machine.TurnCrank(); },
				"You turned but there's no quarter\n");
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct has_quarter_state_Fixture : NaiveGumballMachineFixture
	{
		has_quarter_state_Fixture()
		{
			machine.InsertQuarter();
			machine.InsertQuarter();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_in_has_quarter_state, has_quarter_state_Fixture)
		BOOST_AUTO_TEST_CASE(can_eject_all_quarters)
		{
			CheckFunctionOutput([&]() {
				machine.EjectQuarter(); },
				"Quarter returned\n");
			CheckFunctionOutput([&]() {
					machine.EjectQuarter(); },
					"You haven't inserted a quarter\n");
		}

		BOOST_AUTO_TEST_CASE(can_insert_quarters_while_it_count_less_than_5)
		{
			for (int i=0; i<2;++i)
				machine.InsertQuarter();

			CheckFunctionOutput([&]() {
				machine.InsertQuarter(); },
				"You inserted a quarter\n");

			machine.InsertQuarter();

			CheckFunctionOutput([&]() {
				machine.InsertQuarter(); },
				"You can't insert another quarter\n");
		}

		BOOST_AUTO_TEST_CASE(turn_crank_function_dispense_ball_and_use_quarter)
		{
			CheckFunctionOutput([&]() {
				machine.TurnCrank(); },
				"You turned...\nA gumball comes rolling out the slot\n");
		}
	BOOST_AUTO_TEST_SUITE_END()
	struct SoldOutStateWithQuartersFixture : NaiveGumballMachineFixture
	{
		SoldOutStateWithQuartersFixture()
		{
			machine.InsertQuarter();
			for (unsigned i = 0; i < ballsCount; ++i)
			{
				machine.InsertQuarter();
				machine.TurnCrank();
			}
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_sold_out_state_but_quarters_was_not_ended, SoldOutStateWithQuartersFixture)
		BOOST_AUTO_TEST_CASE(cant_insert_quarter)
		{
			CheckFunctionOutput([&]() {
					machine.InsertQuarter(); },
				"You can't insert a quarter, the machine is sold out\n");
		}
		BOOST_AUTO_TEST_CASE(can_eject_all_quarters)
		{
			CheckFunctionOutput([&]() {
				machine.EjectQuarter(); }, "Quarter returned\n");
		
			CheckFunctionOutput([&]() {
				machine.EjectQuarter(); }, "You haven't inserted a quarter\n");
		}

		BOOST_AUTO_TEST_CASE(turn_crank_function_can_not_release_a_ball)
		{
			CheckFunctionOutput([&]() {
				machine.TurnCrank(); }, "You turned but there's no gumballs\n");
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct SoldOutStateWithoutQuartersFixture : NaiveGumballMachineFixture
	{
		SoldOutStateWithoutQuartersFixture()
		{
			for (unsigned i = 0; i < ballsCount; ++i)
			{
				machine.InsertQuarter();
				machine.TurnCrank();
			}
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_sold_out_state_and_quarters_was_ended, SoldOutStateWithoutQuartersFixture)
		BOOST_AUTO_TEST_CASE(cant_insert_quarter)
		{
			CheckFunctionOutput([&]() {
					machine.InsertQuarter(); }, "You can't insert a quarter, the machine is sold out\n");
		}
		BOOST_AUTO_TEST_CASE(can_not_eject_quarters)
		{
			CheckFunctionOutput([&]() {
				machine.EjectQuarter(); }, "You can't eject, you haven't inserted a quarter yet\n");
		}

		BOOST_AUTO_TEST_CASE(turn_crank_function_can_not_release_a_ball)
		{
			CheckFunctionOutput([&]() {
				machine.TurnCrank(); }, "You turned but there's no gumballs\n");
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
