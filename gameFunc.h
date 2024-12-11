struct player {
    int x;
    int y;
    char direction;
};

void printBoard(char *board []);
void takeInput(struct player *user);
bool movePlayer(struct player *user, char* board []);