#ifndef GAME_H
#define GAME_H

constexpr int M = 3;  // You can change this for your specific game!
constexpr int N = 3;  // You can change this for your specific game!

// Sets every cell of the board to 0 (empty).
void initBoard(int board[M][N], int M, int N);

// Returns 1 if someone has three in a row (the caller decides who from whose
// turn it was), -1 if the board is full with no winner (draw), 0 otherwise.
int parseBoard(int board[M][N]);

// Runs the turn loop until a player wins, the board fills (draw), or input ends.
void gameLoop(int board[M][N], bool cont, int players, int M, int N);

#endif  // GAME_H
