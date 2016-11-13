#ifndef __EXP_VALUE_TABLE_H__
#define __EXP_VALUE_TABLE_H__

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include "my_fib23.h"

using namespace std;

struct exp_value_table{
    double *exp_value;
    int *best_move;

    exp_value_table();
    ~exp_value_table();

    static int hash(state_game &s);

    void set_value(state_game &s, double value);
    void set_move(state_game &s, int move);
    double value(state_game &s);
    int move(state_game &s);

    void save(const char* address);
    void load(const char* address);
};

#endif
