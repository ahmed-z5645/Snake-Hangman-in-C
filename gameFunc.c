#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "gameFunc.h"

#define ROWS 14
#define COLS 49

void printBoard(char* board []){
    for (int i = 0; i < ROWS; i++){
        printf("%s \n", board[i]);
        fflush(stdout);
    }
}

void takeInput(struct player *user){
    char input;
    ssize_t n = read(STDIN_FILENO, &input, 1);
    if(n > 0){
        if (input == 'w' || input == 'a' || input == 's' || input == 'd'){
            user->direction = input;
        }
    }
}

bool movePlayer(struct player *user, char *board []){
    if (user->direction != 'p'){
        char *copy = malloc(COLS);
        if (copy == NULL){ return false; }


        strcpy(copy, board[user->y]);
        copy[user->x] = ' ';
        board[user->y] = copy;
        if (user->direction == 'w'){
            (user->y)--;
        } else if (user->direction == 'a'){
            (user->x)--;
        } else if (user->direction == 's'){
            (user->y)++;
        } else {
            (user->x)++;
        }
        if ((user->x >= COLS) || (user->x < 1) || (user->y >= ROWS) || (user->y < 1)){
            return false;
        } else {
            char *copyTwo = malloc(COLS);
            if (copyTwo == NULL){
                return false;
            }

            strcpy(copyTwo, board[user->y]);
            copyTwo[user->x] = '$';
            board[user->y] = copyTwo;
            return true;
        }
    } else {
        return true;
    }
}