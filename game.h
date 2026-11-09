#ifndef GAME_H
#define GAME_H

constexpr int M = 3;  // You can change this for your specific game!
constexpr int N = 3;  // You can change this for your specific game!

// Sets every cell of the board to 0 (empty).
void initBoard(int board[M][N], int M, int N);

// Returns the winning player p in [1,...,P], or 0 if nobody has won.
int parseBoard(int board[M][N]);

// Runs the turn loop until a player wins.
void gameLoop(int board[M][N], bool cont, int players, int M, int N);

#endif  // GAME_H
