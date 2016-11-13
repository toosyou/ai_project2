#include "my_fib23.h"


const int state_game::mapping_2584[19] = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181};
//                                        0, 1, 2, 3, 4, 5,  6,  7,  8,  9, 10,  11,  12,  13,  14,  15,   16,   17,   18

state_game::state_game(){
    this->valid = true;
    this->score = 0;
    for(int i=0;i<2;++i){
        for(int j=0;j<3;++j){
            this->value_cells[i][j] = 0;
        }
    }
}

state_game::state_game(int board[2][3]){
    this->valid = false;
    this->score = 0;
    map<int, int> value_index;
    for(int i=0;i<19;++i){
        value_index[ this->mapping_2584[i] ] = i;
    }

    for(int i=0;i<2;++i){
        for(int j=0;j<3;++j){
            this->value_cells[i][j] = value_index[board[i][j]];
            if(board[i][j] != 0)
                this->valid = true;
        }
    }
}

state_game::state_game(const state_game& s){
    this->valid = s.valid;
    this->score = s.score;
    for(int i=0;i<2;++i){
        for(int j=0;j<3;++j){
            this->value_cells[i][j] = s.value_cells[i][j];
        }
    }
}

state_game state_game::move(int urdl){
    urdl %= 4;
    switch(urdl){
        case 0:
            return this->up();
            break;
        case 1:
            return this->right();
            break;
        case 2:
            return this->down();
            break;
        case 3:
            return this->left();
            break;
        default:
            break;
    }
    return this->up();
}

state_game state_game::up(){
    if(this->valid == false)
        return *this;

    bool moved = false;
    state_game rtn = *this;
    for(int j=0;j<3;++j){
        if( rtn[0][j] != 0 && rtn[1][j] != 0)
            if( (rtn[0][j] == 1 && rtn[1][j] == 1) ||
                abs(rtn[0][j] - rtn[1][j]) == 1 ){
                rtn[0][j] = max(rtn[0][j], rtn[1][j]) + 1;
                rtn[1][j] = 0;
                rtn.score += this->mapping_2584[rtn[0][j]];
                moved = true;
            }
        if( rtn[0][j] == 0 && rtn[1][j] != 0){
            rtn[0][j] = rtn[1][j];
            rtn[1][j] = 0;
            moved = true;
        }
    }

    rtn.valid = moved;

    return rtn;
}

state_game state_game::down(){
    if(valid == false)
        return *this;

    bool moved = false;
    state_game rtn = *this;
    for(int j=0;j<3;++j){
        if( rtn[0][j] != 0 && rtn[1][j] != 0)
            if( (rtn[0][j] == 1 && rtn[1][j] == 1) ||
                abs(rtn[0][j] - rtn[1][j]) == 1 ){
                rtn[1][j] = max(rtn[0][j], rtn[1][j]) + 1;
                rtn[0][j] = 0;
                rtn.score += this->mapping_2584[rtn[1][j]];
                moved = true;
            }
        if( rtn[1][j] == 0 && rtn[0][j] != 0){
            rtn[1][j] = rtn[0][j];
            rtn[0][j] = 0;
            moved = true;
        }
    }

    rtn.valid = moved;

    return rtn;
}

state_game state_game::left(){
    if(this->valid == false)
        return *this;

    bool moved = false;
    state_game rtn = *this;

    //converge all
    for(int i=0;i<2;++i){
        for(int j=0;j<2;++j){
            if(rtn[i][j] == 0)
                continue;
            //find right
            for(int k=j+1;k<3;++k){
                if(rtn[i][k] == 0)
                    continue;
                if( (rtn[i][k] == 1 && rtn[i][j] == 1) ||
                    abs(rtn[i][k] - rtn[i][j]) == 1){
                    rtn[i][j] = max(rtn[i][j], rtn[i][k]) + 1;
                    rtn[i][k] = 0;
                    rtn.score += this->mapping_2584[rtn[i][j]];
                    moved = true;
                }
                break;
            }
        }
    }

    //move all cell left
    for(int i=0;i<2;++i){
        int k = 0;
        for(int j=0;j<3;++j){
            if(rtn[i][j] != 0){
                rtn[i][k] = rtn[i][j];
                if(k != j)
                    moved = true;
                k++;
            }
        }
        for(;k<3;++k)
            rtn[i][k] = 0;
    }

    rtn.valid = moved;

    return rtn;
}

state_game state_game::right(){
    if(this->valid == false)
        return *this;

    bool moved = false;
    state_game rtn = *this;

    //converge all
    for(int i=0;i<2;++i){
        for(int j=2;j>0;--j){
            if(rtn[i][j] == 0)
                continue;
            //find right
            for(int k=j-1;k>=0;--k){
                if(rtn[i][k] == 0)
                    continue;
                if( (rtn[i][k] == 1 && rtn[i][j] == 1) ||
                    abs(rtn[i][k] - rtn[i][j]) == 1){
                    rtn[i][j] = max(rtn[i][j], rtn[i][k]) + 1;
                    rtn[i][k] = 0;
                    rtn.score += this->mapping_2584[rtn[i][j]];
                    moved = true;
                }
                break;
            }
        }
    }

    //move all cell right
    for(int i=0;i<2;++i){
        int k = 2;
        for(int j=2;j>=0;--j){
            if(rtn[i][j] != 0){
                rtn[i][k] = rtn[i][j];
                if(k != j)
                    moved = true;
                k--;
            }
        }
        for(;k>=0;--k)
            rtn[i][k] = 0;
    }

    rtn.valid = moved;

    return rtn;
}

state_game state_game::random_appear(){
    state_game rtn = *this;

    vector< pair<int, int> > empty_spaces;
    for(int i=0;i<2;++i){
        for(int j=0;j<3;++j){
            if(rtn[i][j] == 0)
                empty_spaces.push_back( pair<int, int>(i, j) );
        }
    }
    if(empty_spaces.empty()){
        rtn.valid = false;
        return rtn;
    }


    int rd_index = rand() % empty_spaces.size();
    int rd_one_or_three = rand() % 100;

    rtn[ empty_spaces[rd_index].first ][ empty_spaces[rd_index].second ] =  (rd_one_or_three < 75) ? 1 : 3;

    return rtn;
}

vector<state_game> state_game::all_appear(){
    vector<state_game> rtn;

    for(int i=0;i<2;++i){
        for(int j=0;j<3;++j){
            if(this->value_cells[i][j] == 0){
                state_game tmp = *this;
                tmp.value_cells[i][j] = 1;
                rtn.push_back(tmp);
                tmp.value_cells[i][j] = 3;
                rtn.push_back(tmp);
            }
        }
    }

    return rtn;
}

short* state_game::operator[](int index){
    return this->value_cells[index];
}

void state_game::print(){
    cout << "======================================" <<endl;
    cout << "score: " << this->score <<endl;
    for(int i=0;i<2;++i){
        for(int j=0;j<3;++j){
            cout << mapping_2584[this->value_cells[i][j]] << "\t";
        }
        cout << endl;
    }

    return;
}

bool state_game::operator==(state_game &s){
    for(int i=0;i<2;++i){
        for(int j=0;j<3;++j){
            if(this->value_cells[i][j] != s[i][j])
                return false;
        }
    }
    return true;
}
