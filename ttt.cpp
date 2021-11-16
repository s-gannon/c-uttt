#include <string>
#include <cstdint>
#include <cstdio>
#include "ttt.h"

#define EMPTY 0
#define X 1
#define O 2
#define DRAW 3

//constructor
ttt::ttt(){
    win_status = EMPTY;
    for(int i = 0; i < 9; i++){
        board[i] = EMPTY;
    }
}
//accessors
int_fast8_t ttt::get_mark_at_pos(int_fast8_t pos){
    try{
        return board[pos];
    } catch(const std::exception& e){
        printf("%s\n", e.what());
    }
}
int_fast8_t ttt::get_win_status(){
    return win_status;
}
//mutators
void ttt::make_move(int_fast8_t mark, int_fast8_t pos){
    try{
        board[pos] = mark;
    } catch(const std::exception& e){
        printf("%s\n", e.what());
    }
    ttt::update_win_status();
}
void ttt::update_win_status(){
    bool is_drawn = true;

    for(int i = 0; i < 9; i++){
        if(board[i] == EMPTY){
            is_drawn = false;
            break;
        }
    }
    if(!is_drawn){
        for(int i = 0; i < 3; i++){
            if(((board[0] == board[4]) && (board[4] == board[8])) || ((board[2] == board[4]) && (board[4] == board[6]))){
                win_status = board[4];
                break;
            }
            else if((board[i*3] == board[(i*3)+1]) && (board[(i*3)+1] == board[(i*3)+2])){
                win_status = board[i*3];
                break;
            }
            else if((board[i] == board[i+3]) && (board[i+3] == board[i+6])){
                win_status = board[i];
                break;
            }
            else{
                win_status = EMPTY;
            }
        }
    }
    else{
        win_status = DRAW;
    }
}
//other functions
void ttt::reset(){
    win_status = EMPTY;
    for(int i = 0; i < 9; i++){
        board[i] = EMPTY;
    }
}
void ttt::print(){
    char cboard[9];
    for(int i = 0; i < 9; i++){
        if(board[i] == X){
            cboard[i] = 'X';
        }
        else if(board[i] == O){
            cboard[i] = 'O';
        }
        else{
            cboard[i] = ' ';
        }
    }
    //could throw this in a for loop and have only 2 statements; refactor later
    printf("%c|%c|%c\n", cboard[0], cboard[1], cboard[2]);
    printf("-+-+-\n");
    printf("%c|%c|%c\n", cboard[3], cboard[4], cboard[5]);
    printf("-+-+-\n");
    printf("%c|%c|%c\n", cboard[6], cboard[7], cboard[8]);
}
bool ttt::check_legal(int_fast8_t pos){
    if(pos >= 0 && pos < 9){
        if(win_status == EMPTY){
            if(board[pos] == EMPTY){
                return true;
            }
        }
    }
    return false;
}
std::string ttt::tostr(){
    std::string fmt = "";
    std::string cboard[9];
    for(int i = 0; i < 9; i++){
        if(board[i] == X){
            cboard[i] = "X";
        }
        else if(board[i] == O){
            cboard[i] = "O";
        }
        else{
            cboard[i] = " ";
        }
    }
    for(int i = 0; i < 3; i++){
        fmt.append(cboard[(i*3)] + "|" + cboard[(i*3)+1] + "|" + cboard[(i*3)+2] + "\n");
        fmt.append(i == 2 ? "\n" : "-+-+-\n");
    }
    return fmt;
}
