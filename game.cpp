#include "game.h"

#include <iostream>
#include <limits>

void initBoard(int board[M][N], int M, int N) {
  for (int m = 0; m < M; m++) {
    for (int n = 0; n < N; n++) {
      board[m][n] = 0;
    }
  }
}

int parseBoard(int board[M][N]) {
  /*
   * Returns 1 if any player has three matching non-empty cells in a line
   * (the caller works out who won from whose turn it was), -1 if the board is
   * full with no winner (a draw), and 0 if the game is still in progress.
   */

  // Check all rows
  for (int m = 0; m < M; m++) {
    if (board[m][0] == board[m][1] && board[m][1] == board[m][2] && board[m][0] != 0) {
      return 1;
    }
  }

  // Check all columns
  for (int n = 0; n < N; n++) {
    if (board[0][n] == board[1][n] && board[1][n] == board[2][n] && board[0][n] != 0) {
      return 1;
    }
  }

  // Check diagonals
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0) {
    return 1;
  }

  if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0) {
    return 1;
  }

  // Check tie (only reached if nobody has won)
  for (int m = 0; m < M; m++) {
    for (int n = 0; n < N; n++) {
      if (board[m][n] == 0) {
        return 0;
      }
    }
  }
  return -1;
}

void gameLoop(int board[M][N], bool cont, int players, int M, int N) {
  int m, n;
  do {
    for (int p = 1; p <= players; ++p) {
      std::cout << "Player " << p << " place:";
      if (!(std::cin >> m >> n)) {
        if (std::cin.eof()) {
          std::cout << "Input ended; game abandoned." << std::endl;
          return;
        }
        // Non-numeric input: discard the line and let the same player retry.
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Illegal move!" << std::endl;
        p--;
        continue;
      }
      if (m < 0 || m >= M || n < 0 || n >= N || board[m][n] != 0) {
        std::cout << "Illegal move!" << std::endl;
        p--;
        continue;
      }

      std::cout << p << " at (" << m << ", " << n << ")." << std::endl;
      board[m][n] = p + 1;

      int check = parseBoard(board);
      if (check == -1) {
        std::cout << "The Game has ended in a Draw." << std::endl;
        cont = false;
        break;
      }
      if (check != 0) {
        std::cout << "Player " << p << " has won!" << std::endl;
        cont = false;
        break;
      }
    }
  } while (cont);
}
