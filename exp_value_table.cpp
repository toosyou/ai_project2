#include "exp_value_table.h"

exp_value_table::exp_value_table(){
    int size = 1 << (6*4);
    this->exp_value = new double[ size ];
    this->best_move = new int[size];
    for(int i=0;i<size;++i){
        this->exp_value[i] = -1;
        this->best_move[i] = -1;
    }
}

exp_value_table::~exp_value_table(){
    delete [] this->exp_value;
}

int exp_value_table::hash(state_game &s){
    int rtn = 0;
    for(int i=0;i<2;++i){
        for(int j=0;j<3;++j){
            rtn <<= 4;
            if(s[i][j] < 16)
                rtn |= s[i][j];
            else
                return -1;
        }
    }
    return rtn;
}

void exp_value_table::set_value(state_game &s, double value){
    int index = exp_value_table::hash(s);
    if(index != -1)
        this->exp_value[index] = value;
    else
        cerr << "index out of range" <<endl;
}

double exp_value_table::value(state_game &s){
    int index = exp_value_table::hash(s);
    if(index != -1)
        return this->exp_value[index];
    else
        return -1;
}

void exp_value_table::set_move(state_game &s, int move){
    int index = exp_value_table::hash(s);
    if(index != -1)
        this->best_move[index] = move;
    else
        cerr << "index out of range" <<endl;
}

int exp_value_table::move(state_game &s){
    int index = exp_value_table::hash(s);
    if(index != -1)
        return this->best_move[index];
    else
        return -1;
}

void exp_value_table::save(const char* address){
    fstream out_table(address, fstream::out | fstream::binary);

    for(int i=0;i<(1 << (6*4)); ++i){
        out_table.write((char*)&this->exp_value[i], sizeof(double));
    }
    for(int i=0;i<(1 << (6*4)); ++i){
        out_table.write((char*)&this->best_move[i], sizeof(int));
    }

    out_table.close();
}

void exp_value_table::load(const char* address){
    fstream in_table(address, fstream::in | fstream::binary);

    if(!in_table.is_open()){
        cerr << "ERROR OPENING " <<address <<endl;
        exit(-1);
    }

    for(int i=0;i<(1 << (6*4)); ++i){
        in_table.read((char*)&this->exp_value[i], sizeof(double) );
    }
    for(int i=0;i<(1 << (6*4)); ++i){
        in_table.read((char*)&this->best_move[i], sizeof(int) );
    }

    in_table.close();
}
