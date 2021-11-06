#ifndef TTT_H_INCLUDED
#define TTT_H_INCLUDED

#include <string>
#include <cstdint>

class ttt{
private:
    int_fast8_t win_status;
    int_fast8_t board[9];
    //mutators
    void update_win_status();
public:
    //constructors
    ttt();
    //accessors
    int_fast8_t get_mark_at_pos(int_fast8_t pos);
    int_fast8_t get_win_status();
    //mutators
    void make_move(int_fast8_t mark, int_fast8_t pos);
    //other
    void reset();
    void print();
    bool check_legal(int_fast8_t pos);
    std::string tostr();
};

#endif // TTT_H_INCLUDED
