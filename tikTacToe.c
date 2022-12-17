#include <stdio.h>
#include <stdlib.h>

#define ROWS 3
#define COLS 3

// Function prototypes
void initializeBoard(char board[ROWS][COLS]);
void printBoard(char board[ROWS][COLS]);
int checkWin(char board[ROWS][COLS]);
int checkFull(char board[ROWS][COLS]);
void placeMove(char board[ROWS][COLS]);

int main(void)
{
    char board[ROWS][COLS];
    int row, col;
    int win = 0;
    int full = 0;

    // Initialize the board
    initializeBoard(board);

    // Main game loop
    while (!win && !full)
    {
        // Print the board
        printBoard(board);

        // Get row and col inputs from player
        printf("Enter row and column: ");
        scanf("%d%d", &row, &col);

        // Make sure the inputs are valid
        if (row < 0 || row >= ROWS || col < 0 || col >= COLS || board[row][col] != ' ')
        {
            printf("Invalid move, try again.\n");
            continue;
        }

        // Place the player's marker on the board
        board[row][col] = 'X';

        // Check for a win or full board
        win = checkWin(board);
        full = checkFull(board);

        placeMove(board);
    }

    // Print the final board and declare the winner
    printBoard(board);
    if (win)
    {
        printf("You lose!\n");
    }
    else
    {
        printf("It's a draw!\n");
    }

    return 0;
}

// Initialize the board to all spaces
void initializeBoard(char board[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = ' ';
        }
    }
}

// Print the current state of the board
void printBoard(char board[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        printf(" ");
        for (int j = 0; j < COLS; j++)
        {
            printf("%c", board[i][j]);
            if (j < COLS - 1)
            {
                printf(" | ");
            }
        }
        printf(" ");
        printf("\n");
        if (i < ROWS - 1)
        {
            printf("-----------\n");
        }
    }
    printf("\n");
}

// Check if the given player has won
int checkWin(char board[ROWS][COLS])
{
    // Check rows
    for (int i = 0; i < ROWS; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
        {
            return 1;
        }
    }

    // Check columns
    for (int i = 0; i < COLS; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
        {
            return 1;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
    {
        return 1;
    }
    if (board[2][0] == board[1][1] && board[1][1] == board[0][2] && board[2][0] != ' ')
    {
        return 1;
    }

    // No win found
    return 0;
}

// Check if the board is full
int checkFull(char board[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == ' ')
            {
                return 0;
            }
        }
    }
    return 1;
}

void placeMove(char board[ROWS][COLS])
{
    // First, try to win by placing an O in a winning position
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'O';
                if (checkWin(board))
                {
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // Next, try to block the opponent's win by placing an O in a position where the opponent would win
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'X';
                if (checkWin(board))
                {
                    board[i][j] = 'O';
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // If neither of the above strategies work, place an O in the first empty space we find
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'O';
                return;
            }
        }
    }
}
