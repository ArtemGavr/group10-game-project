#include <cstdlib>
#include <iostream>

#include "game.h"

int main(void) {
  int P;
  bool cont = true;
  //if (argc < 1) {
    //return EXIT_FAILURE;
  std::cout << "Initialising game... How many players?";
  std::cin >> P;
  int board[M][N];
  initBoard(board, M, N);
  gameLoop(board, cont, P, M, N);
  return EXIT_SUCCESS;
}
