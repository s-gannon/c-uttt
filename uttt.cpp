#include <string>
#include <cstdint>
#include <cstdio>
#include "ttt.h"
#include "uttt.h"

#define EMPTY 0
#define X 1
#define O 2
#define DRAW 3

//constructor
uttt::uttt(){
    win_status = EMPTY;
    for(int i = 0; i < 9; i++){
        ttt new_game;
        board[i] = new_game;
    }
}
//accessors
int_fast8_t uttt::get_mark_at_pos(int_fast8_t subboard, int_fast8_t pos){
    try{
        return board[subboard].get_mark_at_pos(pos);
    } catch(const std::exception& e){
        printf("%s\n", e.what());
    }
    return 0;
}
ttt uttt::get_subboard(int_fast8_t subboard){
    return board[subboard];
}
int_fast8_t uttt::get_win_status(){
    return win_status;
}
//mutators
void uttt::make_move(int_fast8_t mark, int_fast8_t subboard, int_fast8_t pos){
    try{
        board[subboard].make_move(mark, pos);
    } catch(const std::exception& e){
        printf("%s\n", e.what());
    }
    uttt::update_win_status();
}
void uttt::update_win_status(){
    bool is_drawn = true;
    int_fast8_t b[9];       //win statuses of all of the subboards

    for(int i = 0; i < 9; i++){
        b[i] = board[i].get_win_status();
        if(b[i] == EMPTY){
            is_drawn = false;
        }
    }
    if(!is_drawn){
        for(int i = 0; i < 3; i++){
            if(((b[0] == b[4]) && (b[4] == b[8])) || ((b[2] == b[4]) && (b[4] == b[6]))){
                win_status = b[4];
                break;
            }
            else if((b[i*3] == b[(i*3)+1]) && (b[(i*3)+1] == b[(i*3)+2])){
                win_status = b[i*3];
                break;
            }
            else if((b[i] == b[i+3]) && (b[i+3] == b[i+6])){
                win_status = b[i];
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
void uttt::reset(){
    win_status = EMPTY;
    for(int i = 0; i < 9; i++){
        board[i].reset();
    }
}
void uttt::print(){
    for(int w = 0; w < 3; w++){
        for(int x = 0; w < 3; w++){
            for(int y = 0; w < 3; w++){
                for(int z = 0; w < 3; w++){
                    int_fast8_t pos = board[y + (w*3)].get_mark_at_pos(z + (x*3));
                    if(pos == X){
                        printf("X");
                    }
                    else if(pos == O){
                        printf("O");
                    }
                    else{
                        printf(" ");
                    }
                    if(!((y == z) && (z == 2))){
                        printf("|");
                    }
                }
            }
            if(x != 2){
                printf("\n-+-+-|-+-+-|-+-+-\n");
            }
        }
        if(w != 2){
            printf("\n-----+-----+-----\n");
        }
    }
    printf("\n");
}
bool uttt::check_legal(int_fast8_t lastpos, int_fast8_t subboard, int_fast8_t pos){
    if(lastpos == -1){
        if((subboard >= 0 && subboard < 9) && (pos >= 0 && pos < 9)){
            if(board[subboard].check_legal(pos)){
                return true;
            }
        }
    }
    else if((subboard >= 0 && subboard < 9) && (lastpos >= 0 && lastpos < 9) && (pos >= 0 && pos < 9)){
        if(board[lastpos].get_win_status() == EMPTY){
            if(lastpos == subboard){
                if(board[subboard].check_legal(pos)){
                    return true;
                }
            }
        }
        else{
            if(lastpos != subboard){
                if(board[subboard].check_legal(pos)){
                    return true;
                }
            }
        }
    }
    return false;
}
std::string uttt::tostr(){
    std::string fmt = "";
    for(int w = 0; w < 3; w++){         //"It just works" - Todd Howard
        for(int x = 0; w < 3; w++){
            for(int y = 0; w < 3; w++){
                for(int z = 0; w < 3; w++){
                    int_fast8_t pos = board[y + (w*3)].get_mark_at_pos(z + (x*3));
                    if(pos == X){
                        fmt.append("X");
                    }
                    else if(pos == O){
                        fmt.append("O");
                    }
                    else{
                        fmt.append(" ");
                    }
                    if(!((y == z) && (z == 2))){    //if y == z and z == 2, then y also == 2 via transitivity
                        fmt.append("|");
                    }
                }
            }
            if(x != 2){
                fmt.append("\n-+-+-|-+-+-|-+-+-\n");
            }
        }
        if(w != 2){
            fmt.append("\n-----+-----+-----\n");
        }
    }
    return fmt + "\n";
}
