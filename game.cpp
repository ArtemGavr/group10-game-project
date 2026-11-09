#include "game.h"

#include <iostream>

void initBoard(int board[M][N], int M, int N) {
  for (int m = 0; m < M; m++) {
    for (int n = 0; n < N; n++) {
      board[m][n] = 0;
    }
  }
}

int parseBoard(int board[M][N]) {
  /*
   * This function is where you should define your win conditions.
   * If player p in [1,...,P] has won, then you should return p; otherwise 0.
   * If you find yourself with a great deal of spare time you might try
   * rendering the board to the terminal here, too.
   */

  // Check all verticals 
  for (int m = 0; m < M; m++) {
    if (board[m][0] == board[m][1] && board[m][1] == board[m][2] && board[m][0] != 0 ){
      //std::cout<<"Verticals ";
      return 1;
      
    }
  }
  //Check all horizontals
  for (int n = 0; n < N; n++) {
    if (board[0][n] == board[1][n] && board[1][n] == board[2][n] && board[0][n] != 0 ){
      //std::cout<<"horizontals ";
      return 1;
      
    }
  }

  //Check Diagonals
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0 ){
    //std::cout<<"diagonals";
    return 1;
    
  }

  if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0 ){
    //std::cout<<"diagonals";
    return 1;
  }

  //Check tie
  bool tieCheck = true;
  for(int m = 0; m<M; m++){
    for(int n = 0; n<N; n++){
      if (board[m][n] == 0){
        tieCheck = false;
      }
    }
  }
  if (tieCheck){
    return -1;
  }
  
  return 0;
}

void gameLoop(int board[M][N], bool cont, int players, int M, int N) {
  int winner;
  int m, n;
  do {
    for (int p = 1; p <= players; ++p) {
      std::cout << "Player " << p << " place:";
      std::cin >> m >> n;
      if (board[m][n] == 0) {
        std::cout << p << " at (" << m << ", " << n << ")." << std::endl;
        board[m][n] = p+1;
      } else {
        std::cout << "Illegal move!" << std::endl;
        p--;
      }
      winner = p;
    }
    int check = parseBoard(board);
    if (check != 0) {
      if(check == -1){
        std::cout << "The Game has ended in a Draw." << std::endl;
      }
      else{
        std::cout << "Player " << winner << " has won!" << std::endl;
        cont = false;
      }
    }
  } while (cont);
}
