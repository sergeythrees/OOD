#include "NaiveGumBallMachine.h"
#include "GumBallMachineWithState.h"
#include "GumBallMachineWithState.h"

using namespace std;

template <typename GumballMachineType>
void TestGumballMachine(GumballMachineType & m)
{
	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.TurnCrank();

	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.EjectQuarter();
	m.TurnCrank();

	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.EjectQuarter();

	cout << m.ToString() << endl;

	m.InsertQuarter();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();
	m.InsertQuarter();
	m.TurnCrank();

	cout << m.ToString() << endl;
}

void TestNaiveGumballMachine()
{
	naive::CGumballMachine m(2);
	TestGumballMachine(m);
}

void TestGumballMachineWithState()
{
	with_state::CGumballMachine m(5);
	TestGumballMachine(m);
}

int main()
{
	with_state::CGumballMachine machine(2);
	cout << machine.ToString();
	machine.TurnCrank();
	//TestNaiveGumballMachine();

	cout << "\n-----------------\n";
//	TestGumballMachineWithState();

	return 0;
}
