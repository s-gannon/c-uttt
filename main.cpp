//MPI and #pragma tags commented out for debugging purposes
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdio>
#include <ctime>
#include <string>
//#include <mpi.h>
#include "uttt.h"
#include "ttt.h"

#define EMPTY 0
#define X 1
#define O 2
#define DRAW 3
#define ASCII_OFFSET 33
#define MIN_WIN_DEPTH 17
#define MAX_NUM_MOVES 81
//trying to keep these magic numbers to a minimum

void recursive_make_move(uttt uttt_obj, int_fast8_t mark, int_fast8_t lastpos, std::string gamestr, std::string filename, int_fast8_t depth, bool only_wins){
    if(depth <= 0){
        if(uttt_obj.get_win_status() != EMPTY){
            std::ofstream file;
            char winchar = 0;

            if(uttt_obj.get_win_status() == O)
                winchar = '0';
            else if(uttt_obj.get_win_status() == X)
                winchar = '1';
            else if(uttt_obj.get_win_status() == DRAW)
                winchar = '2';
            //following checks the last 4 chars of the string to see if they're .txt
            std::string end = "";
            try{
                for(int i = 0; i < 4; i++){
                    end = filename[filename.length()-(1+i)];
                }
            } catch(const std::exception &e){
                printf("%s\n", e.what());
            }
            //if .txt, then go ahead; else, add .txt to the end and go ahead
            if(end.compare(".txt") == 0)
                file.open(filename, std::ios_base::app);
            else
                file.open(filename + ".txt", std::ios_base::app);
            file << gamestr << winchar << "\n";
            //I was told by Stack Overflow that file does not need to be closed
            return;
        }
        else if(!only_wins){
            std::ofstream file;
            std::string end = "";
            try{
                for(int i = 0; i < 4; i++){
                    end = filename[filename.length()-(1+i)];
                }
            } catch(const std::exception &e){
                printf("%s\n", e.what());
            }
            //if .txt, then go ahead; else, add .txt to the end and go ahead
            if(end.compare(".txt") == 0)
                file.open(filename, std::ios_base::app);
            else
                file.open(filename + ".txt", std::ios_base::app);
            file << gamestr << "\n";
            //I was told by Stack Overflow that file does not need to be closed
            return;
        }
    }
    else{
        int_fast8_t next_subboard = lastpos;
        if(next_subboard == -1){
            for(int sub = 0; sub < 9; sub++){
                for(int pos = 0; pos < 9; pos++){
                    if(uttt_obj.check_legal(lastpos, sub, pos)){
                        uttt_obj.make_move(mark, sub, pos);
                        filename = (filename != "" ? filename : (std::to_string(sub) + std::to_string(pos) + "_games"));
                        if(uttt_obj.get_subboard(pos).get_win_status() != EMPTY)
                            recursive_make_move(uttt_obj, (mark == X ? O : X), -1, gamestr + std::to_string(std::stoi(std::to_string(sub) + std::to_string(pos), nullptr) + ASCII_OFFSET), filename, depth - 1, only_wins);
                        else
                            recursive_make_move(uttt_obj, (mark == X ? O : X), pos, gamestr + std::to_string(std::stoi(std::to_string(sub) + std::to_string(pos), nullptr) + ASCII_OFFSET), filename, depth - 1, only_wins);
                        uttt_obj.make_move(EMPTY, sub, pos);
                    }
                }
            }
        }
        else{
            for(int pos = 0; pos < 9; pos++){
                if(uttt_obj.check_legal(lastpos, next_subboard, pos)){
                    uttt_obj.make_move(mark, next_subboard, pos);
                    filename = (filename != "" ? filename : (std::to_string(next_subboard) + std::to_string(pos) + "_games"));
                    if(uttt_obj.get_subboard(next_subboard).get_win_status() != EMPTY)
                        recursive_make_move(uttt_obj, (mark == X ? O : X), -1, gamestr + std::to_string(std::stoi(std::to_string(next_subboard) + std::to_string(pos), nullptr) + ASCII_OFFSET), filename, depth - 1, only_wins);
                    else
                        recursive_make_move(uttt_obj, (mark == X ? O : X), pos,  gamestr + std::to_string(std::stoi(std::to_string(next_subboard) + std::to_string(pos), nullptr) + ASCII_OFFSET), filename, depth - 1, only_wins);
                    uttt_obj.make_move(EMPTY, next_subboard, pos);
                }
            }
        }
    }
}

int main(){
    time_t timer;
    bool keepwins = false;
    int_fast8_t start_subboard, start_pos, depth;
    start_subboard = -1;
    start_pos = -1;

    printf("Enter a starting move, subboard, and depth or \'-1 -1 -1\' to specify to start from beginning with no depth: ");
    std::cin >> start_subboard >> start_pos >> depth;
    std::cin.ignore();  //clear the input
    if(depth >= MIN_WIN_DEPTH){
        char input;
        printf("Keep only wins? (y/n): ");  //why is this printing in instances when the if evals false?? fuck me I guess
        std::cin >> input;
        if(input == 'n' || input == 'N'){
            keepwins = false;
        }
        else{
            keepwins = true;
        }
    }

    time(&timer);   //start the clock
    if(start_subboard != -1 && start_pos != -1){
        //#pragma omp parallel for
        for(int_fast8_t i = 0; i < 9; i++){
            uttt game;
            std::string gamestr = "";

            game.make_move(X, start_subboard, start_pos);   //move #1 made
            gamestr.append(std::to_string(std::stoi(std::to_string(start_subboard) + std::to_string(start_pos), nullptr) + ASCII_OFFSET));
            if(game.check_legal(start_pos, start_pos, i)){
                game.make_move(O, start_pos, i);            //move #2 made
                gamestr.append(std::to_string(std::stoi(std::to_string(start_pos) + std::to_string(i), nullptr) + ASCII_OFFSET));
                recursive_make_move(game, X, i, gamestr, std::to_string(start_subboard) + std::to_string(start_pos) + "_games", (depth == -1 ? MAX_NUM_MOVES - 2 : depth), keepwins);
            }
        }
    }
    else if(start_subboard == -1 && start_pos != -1){
        //#pragma omp parallel for
        for(int_fast8_t pos = 0; pos < 9; pos++){
            uttt game;
            std::string gamestr = "";

            gamestr.append(std::to_string(std::stoi(std::to_string(start_subboard) + std::to_string(pos), nullptr) + ASCII_OFFSET));
            game.make_move(X, start_subboard, pos);     //move #1 made
            recursive_make_move(game, O, pos, gamestr, std::to_string(start_subboard) + std::to_string(pos) + "_games", (depth == -1 ? MAX_NUM_MOVES - 1 : depth), keepwins);
        }
    }
    else{
        //#pragma omp parallel for
        for(int_fast8_t subpos = 0; subpos < 9; subpos++){
            uttt game;
            recursive_make_move(game, X, subpos, "", std::to_string(subpos) + "X_games", (depth == -1 ? MAX_NUM_MOVES : depth), keepwins);
        }
    }

    printf("\nProcesses finished. Runtime: %.4f seconds\n", difftime(time(NULL), timer));
    return 0;
}
