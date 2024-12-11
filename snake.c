#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <fcntl.h> // For fcntl()

#include "gameFunc.h"

#define ROWS 14
#define COLS 49

//disable canonical mode, so that user does not have to press enter on input
void setNonCanonicalMode() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t); // Get the current terminal attributes
    t.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &t); // Apply changes immediately
}

//turn terminal back to original settings
void restoreTerminalMode(struct termios *original) {
    tcsetattr(STDIN_FILENO, TCSANOW, original);
}

//set non blocking so that it continues even if no user input
void setNonBlockingMode() {
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void resetNonBlockingMode() {
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0); // Get current file descriptor flags
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK); // Unset non-blocking mode
}

int main() {

    //init all the pieces of the game
    char *board [] = {
        "#################################################",
        "#                                               #",
        "#                                               #",
        "#                                               #",
        "#                                               #",
        "#                                               #",
        "#                       $                       #",
        "#                                               #",
        "#                                               #",
        "#                                               #",
        "#                                               #",
        "#                                               #",
        "#                                               #",
        "#################################################"
        };

    struct player *user = malloc(sizeof(struct player));
    if(user == NULL){
        return EXIT_FAILURE;
    }
    user->direction = 'p';
    user->x = 24;
    user->y = 6;

    int currLetters [5][2];
    for (int i = 0; i < 5; i++){
        currLetters[i][0] = 1;
        currLetters[i][1] = 1;
    }

    srand(time(NULL));
    char * hiddenString = getRandomString();
    char displayString [strlen(hiddenString)];
    getDisplayString(displayString, hiddenString);

    //alter terminal
    struct termios original;
    tcgetattr(STDIN_FILENO, &original); // Save the original terminal attributes
    setNonCanonicalMode();
    setNonBlockingMode();

    //start game!
    mutateBoard(board, currLetters);
    bool gameRunning = true;
    //game running
    while(gameRunning){
        printf("\033[H\033[J");
        takeInput(user);
        gameRunning = movePlayer(user, board, currLetters, displayString, hiddenString);
        printBoard(board, displayString);
        usleep(100000);
    }

    //Clean up
    free(user);
    restoreTerminalMode(&original);
    resetNonBlockingMode();

    printf("\n");
    return EXIT_SUCCESS;
}