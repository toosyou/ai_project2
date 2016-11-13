#include "Fib2x3Solver.h"

Fib2x3Solver::Fib2x3Solver()
{
}

void Fib2x3Solver::initialize(int argc, char* argv[])
{
	table.load("1114.exp");
}

double Fib2x3Solver::evaluteExpectedScore(int arrayboard[2][3])
{
	state_game game(arrayboard);

	return table.value(game);
}

// 0: up
// 1: right
// 2: down
// 3: left
// -1: cannot move
int Fib2x3Solver::findBestMove(int arrayboard[2][3])
{
	state_game game(arrayboard);

	int rtn = table.move(game);
	if( rtn == -1 )
		return 4;
	return rtn;
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
