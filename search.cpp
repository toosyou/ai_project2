#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include "exp_value_table.h"
#include "my_fib23.h"

using namespace std;

exp_value_table table;

double exp(state_game s, int depth = 0){

    double table_value = table.value(s);
    if( table_value != -1)
        return table_value;

    double max_value = 0.0;
    int best_move = 4;
    s.score = 0;
    vector<state_game> all_moves;
    vector<int> move_index;
    for(int i=0;i<4;++i){
        state_game next = s.move(i);
        if(next.valid){
            all_moves.push_back(next);
            move_index.push_back(i);
        }
    }

    for(unsigned int i=0;i<all_moves.size();++i){
        double score_already_have = (double)all_moves[i].score;
        vector<state_game> all_appears = all_moves[i].all_appear();
        double avg_value = 0.0;
        const double size_empty = (double)all_appears.size() / 2.0;
        for(unsigned int j=0;j<all_appears.size();j+=2){
            avg_value += exp(all_appears[j], depth+1) * 0.75 / size_empty;
            avg_value += exp(all_appears[j+1], depth+1) * 0.25 / size_empty;
        }
        avg_value += score_already_have;
        if( max_value < avg_value ){
            max_value = avg_value;
            best_move = move_index[i];
        }
    }

    table.set_value(s, max_value);
    table.set_move(s, best_move);

    return max_value;
}

int main(void){

    int test_board[5][2][3] = {
        {
            {8, 34, 1},
            {8, 8, 2}
        },
        {
            {5, 21, 21},
            {21, 5, 3}
        },
        {
            {5, 144, 144},
            {21, 1, 1}
        },
        {
            {0, 3, 0},
            {34, 144, 3}
        },
        {
            {2584, 55, 8},
            {3, 2, 144}
        }
    };

    /*state_game game;
    vector<state_game> all_appears = game.all_appear();
    for(unsigned int i=0;i<all_appears.size();++i){
        exp(all_appears[i]);
        cout << i <<endl;
    }
    table.save("1114.exp");*/

    table.load("1114.exp");
    for(int i=0;i<5;++i){
        state_game game(test_board[i]);
        cout << table.move(game) <<endl;
        cout << table.value(game) <<endl;
    }


    return 0;
}
