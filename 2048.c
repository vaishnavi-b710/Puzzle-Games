#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4

int board[SIZE][SIZE];
int score = 0;

// to print the game board
void printBoard() {
    system("clear || cls");
    printf("\n\t===== 2048 Game =====\n");
    printf("\tScore: %d\n", score);
    for (int i = 0; i < SIZE; i++) {
        printf("\t-----------------------------\n\t|");
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0)
                printf("     |");
            else
                printf(" %4d|", board[i][j]);
        }
        printf("\n");
    }
    printf("\t-----------------------------\n");
    printf("Controls: W=Up S=Down A=Left D=Right R=Reset Q=Quit\n");
}

// adding a random 2 or 4 to the board
void addRandomTile() {
    int empty[SIZE * SIZE][2];
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                empty[count][0] = i;
                empty[count][1] = j;
                count++;
            }
        }
    }
    if (count > 0) {
        int r = rand() % count;
        int val = (rand() % 10 < 9) ? 2 : 4;
        board[empty[r][0]][empty[r][1]] = val;
    }
}

// to compress and merge one row or column
int compressLine(int *line) {
    int temp[SIZE] = {0};      // to build new line
    int merged[SIZE] = {0};    // track merged indices
    int idx = 0;

    // merge logic
    for (int i = 0; i < SIZE; i++) {
        if (line[i] == 0) continue;

        if (idx > 0 && temp[idx - 1] == line[i] && !merged[idx - 1]) {
            temp[idx - 1] *= 2;
            score += temp[idx - 1];
            merged[idx - 1] = 1;
        } else {
            temp[idx++] = line[i];
        }
    }

    // check if line changed
    int moved = 0;
    for (int i = 0; i < SIZE; i++) {
        if (line[i] != temp[i]) {
            moved = 1;
            line[i] = temp[i];
        }
    }

    return moved;
}



// Move functions
int moveLeft() {
    int moved = 0;
    for (int i = 0; i < SIZE; i++)
        moved |= compressLine(board[i]);
    return moved;
}

int moveRight() {
    int moved = 0;
    for (int i = 0; i < SIZE; i++) {
        int line[SIZE];
        for (int j = 0; j < SIZE; j++)
            line[j] = board[i][SIZE - 1 - j];
        moved |= compressLine(line);
        for (int j = 0; j < SIZE; j++)
            board[i][SIZE - 1 - j] = line[j];
    }
    return moved;
}

int moveUp() {
    int moved = 0;
    for (int j = 0; j < SIZE; j++) {
        int line[SIZE];
        for (int i = 0; i < SIZE; i++)
            line[i] = board[i][j];
        moved |= compressLine(line);
        for (int i = 0; i < SIZE; i++)
            board[i][j] = line[i];
    }
    return moved;
}

int moveDown() {
    int moved = 0;
    for (int j = 0; j < SIZE; j++) {
        int line[SIZE];
        for (int i = 0; i < SIZE; i++)
            line[i] = board[SIZE - 1 - i][j];
        moved |= compressLine(line);
        for (int i = 0; i < SIZE; i++)
            board[SIZE - 1 - i][j] = line[i];
    }
    return moved;
}

// Reset 
void resetBoard() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = 0;
    score = 0;
    addRandomTile();
    addRandomTile();
}

// Check for possible moves
int hasMoves() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0)
                return 1;
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j])
                return 1;
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1])
                return 1;
        }
    }
    return 0;
}

int main() {
    srand(time(NULL));
    resetBoard();
    printBoard();

    char ch;
    while (1) {
        ch = getchar();
        while (getchar() != '\n'); // Clear buffer

        int moved = 0;
        if (ch == 'w' || ch == 'W') moved = moveUp();
        else if (ch == 's' || ch == 'S') moved = moveDown();
        else if (ch == 'a' || ch == 'A') moved = moveLeft();
        else if (ch == 'd' || ch == 'D') moved = moveRight();
        else if (ch == 'r' || ch == 'R') { 
            resetBoard(); 
            printBoard(); 
            continue;      
            }
        else if (ch == 'q' || ch == 'Q') break;

        if (moved) addRandomTile();
        printBoard();

        if (!hasMoves()) {
            printf("\nGame Over! Final Score: %d\n", score);
            break;
        }
    }

    return 0;
}
