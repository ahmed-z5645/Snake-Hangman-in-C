struct player {
    int x;
    int y;
    char direction;
};

void printBoard(char *board [], char* displayString);
void takeInput(struct player *user);
bool movePlayer(struct player *user, char* board [], int curLetters [5][2], char *displayString, char *hiddenString);
char *getRandomString();
void getDisplayString(char *displayString, char *hiddenString);
bool fillDisplayString(char letter, char *displayString, char *hiddenString);
void mutateBoard(char * board [], int currLetters [5][2]);