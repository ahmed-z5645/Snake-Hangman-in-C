struct player {
    int x;
    int y;
    char direction;
};

void printBoard(char *board []);
void takeInput(struct player *user);
bool movePlayer(struct player *user, char* board []);
char *getRandomString();
void getDisplayString(char *displayString);
bool fillDisplayString(char letter, char *displayString, char *hiddenString);
void mutateBoard(char * board []);