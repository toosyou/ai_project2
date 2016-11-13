#ifndef __MY_FIB23_H__
#define __MY_FIB23_H__

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <utility>
#include <map>

using namespace std;

struct state_game{
    bool valid;
    int score;

    short value_cells[2][3];
    static const int mapping_2584[19];

    state_game();
    state_game(int board[2][3]);
    state_game(const state_game& s);

    state_game move(int urdl);

    state_game up();
    state_game down();
    state_game left();
    state_game right();

    state_game random_appear();

    vector<state_game> all_appear();

    bool operator==(state_game &s);
    short* operator[](int index);
    void print();
};

#endif
