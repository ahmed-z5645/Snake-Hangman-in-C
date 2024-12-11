#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "gameFunc.h"

#define ROWS 14
#define COLS 49

void printBoard(char* board [], char* displayString){
    printf("\"%s\" \n ", displayString);
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

bool movePlayer(struct player *user, char *board [], int currLetters[5][2], char *displayString, char *hiddenString){
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
        if ((user->x >= COLS - 1) || (user->x < 1) || (user->y >= ROWS - 1) || (user->y < 1)){
            return false;
        } else {
            char *copyTwo = malloc(COLS);
            if (copyTwo == NULL){
                return false;
            }

            strcpy(copyTwo, board[user->y]);
            copyTwo[user->x] = '$';
            char temp = board[user->y][user->x];
            if (temp != ' '){
                bool isWin = fillDisplayString(temp, displayString, hiddenString);
                if (isWin){
                    return false;
                }
                mutateBoard(board, currLetters);
            }
            board[user->y] = copyTwo;
            return true;
        }
    } else {
        return true;
    }
}

char *getRandomString(){
    char *arrOfStrings [] = {
        "I will pass my exams",
        "Ahmed is so cool",
        "Swe is better than tron",
        "I need to lock in",
        "Chromakopia album of the year"
    };

    int key = rand() % 5;

    return arrOfStrings[key];
}

void getDisplayString(char displayString[], char *hiddenString){
    for (int i = 0; i < strlen(hiddenString); i++){
        if (hiddenString[i] != ' '){
            displayString[i] = '_';
        } else {
            displayString[i] = ' ';
        }
    }
    displayString[strlen(hiddenString)] = '\0';
}

bool fillDisplayString(char letter, char *displayString, char *hiddenString){
    int count = 0;
    for (int i = 0; i < strlen(displayString); i++){
        if (letter == hiddenString[i] || letter == (hiddenString[i] - 32)){
            displayString[i] = letter;
        }

        if (displayString[i] == '_'){
            count++;
        }
    }

    if (count == 0){
        return true;
    } else {
        return false;
    }
}

void mutateBoard(char * board [], int currLetters [5][2]){

    for (int i = 0; i< 5; i++){
        char *clearLetters = malloc(COLS);
        if (clearLetters == NULL){
            exit(1);
        }
        
        strcpy(clearLetters, board[currLetters[i][1]]);
        clearLetters[currLetters[i][0]] = ' ';
        board[currLetters[i][1]] = clearLetters;
        
    }

    for (int i = 0; i < 5; i++){
        char randomLetter = 'A' + (random() % 26);
        int randomX = (random() % (COLS - 2)) + 1;
        int randomY = (random() %(ROWS - 2)) + 1;

        char *newLine = malloc(COLS);
        if (newLine == NULL){
            exit (1);
        }

        strcpy(newLine, board[randomY]);
        if (newLine[randomX] != '$'){
            newLine[randomX] = randomLetter;
        } else if (randomX == (COLS - 1)){
            newLine[(randomX - 1)] = randomLetter;
        } else {
            newLine[(randomX + 1)] = randomLetter;
        }

        board[randomY] = newLine;

        currLetters[i][0] = randomX;
        currLetters[i][1] = randomY;
    }
}