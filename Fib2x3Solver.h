#ifndef __FIB2X3SOLVER_H__
#define __FIB2X3SOLVER_H__

// include anything you might use
#include "my_fib23.h"
#include "exp_value_table.h"

class Fib2x3Solver
{
	exp_value_table table;
public:
	Fib2x3Solver();
	// initialize solver
	void initialize(int argc, char* argv[]);
	// do some action when game over
	double evaluteExpectedScore(int board[2][3]);
	int findBestMove(int board[2][3]);

	/**********************************
	You can implement any additional functions
	or define any variables you may need.
	**********************************/
private:

};

#endif
