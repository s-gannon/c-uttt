#ifndef UTTT_H_INCLUDED
#define UTTT_H_INCLUDED

#include <string>
#include <cstdint>
#include "ttt.h"

class uttt{
private:
    ttt board[9];
    int_fast8_t win_status;
    //mutators
    void update_win_status();
public:
    //constructors
    uttt();
    //accessors
    int_fast8_t get_mark_at_pos(int_fast8_t subboard, int_fast8_t pos);
    ttt get_subboard(int_fast8_t subboard);
    int_fast8_t get_win_status();
    //mutators
    void make_move(int_fast8_t mark, int_fast8_t subboard, int_fast8_t pos);
    //other
    void reset();
    void print();
    bool check_legal(int_fast8_t lastpos, int_fast8_t subboard, int_fast8_t pos);
    std::string tostr();
};

#endif // TTT_H_INCLUDED
