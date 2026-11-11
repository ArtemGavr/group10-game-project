#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <string>

#include "game.h"

namespace {

// Fills a board from a row-major list of 9 values.
void fill(int board[M][N], const int (&v)[M * N]) {
  for (int m = 0; m < M; m++)
    for (int n = 0; n < N; n++) board[m][n] = v[m * N + n];
}

// Runs gameLoop with the given stdin text and returns everything printed.
std::string play(int board[M][N], const std::string& input, int players = 2) {
  std::istringstream in(input);
  std::ostringstream out;
  std::streambuf* oldIn = std::cin.rdbuf(in.rdbuf());
  std::streambuf* oldOut = std::cout.rdbuf(out.rdbuf());
  std::cin.clear();
  gameLoop(board, true, players, M, N);
  std::cin.rdbuf(oldIn);
  std::cout.rdbuf(oldOut);
  std::cin.clear();
  return out.str();
}

bool contains(const std::string& s, const std::string& sub) {
  return s.find(sub) != std::string::npos;
}

}  // namespace

// ---------- initBoard ----------

TEST(InitBoard, SetsEveryCellToZero) {
  int board[M][N];
  for (int m = 0; m < M; m++)
    for (int n = 0; n < N; n++) board[m][n] = 7;
  initBoard(board, M, N);
  for (int m = 0; m < M; m++)
    for (int n = 0; n < N; n++) EXPECT_EQ(board[m][n], 0);
}

// ---------- parseBoard ----------

TEST(ParseBoard, EmptyBoardIsInProgress) {
  int board[M][N];
  initBoard(board, M, N);
  EXPECT_EQ(parseBoard(board), 0);
}

TEST(ParseBoard, PartiallyFilledNoLineIsInProgress) {
  int board[M][N];
  const int v[9] = {1, 2, 0,
                    0, 1, 0,
                    0, 0, 2};
  fill(board, v);
  EXPECT_EQ(parseBoard(board), 0);
}

TEST(ParseBoard, DetectsEachRow) {
  for (int r = 0; r < M; r++) {
    int board[M][N];
    initBoard(board, M, N);
    for (int n = 0; n < N; n++) board[r][n] = 1;
    EXPECT_EQ(parseBoard(board), 1) << "row " << r;
  }
}

TEST(ParseBoard, DetectsEachColumn) {
  for (int c = 0; c < N; c++) {
    int board[M][N];
    initBoard(board, M, N);
    for (int m = 0; m < M; m++) board[m][c] = 1;
    EXPECT_EQ(parseBoard(board), 1) << "column " << c;
  }
}

TEST(ParseBoard, DetectsMainDiagonal) {
  int board[M][N];
  const int v[9] = {1, 0, 0,
                    0, 1, 0,
                    0, 0, 1};
  fill(board, v);
  EXPECT_EQ(parseBoard(board), 1);
}

TEST(ParseBoard, DetectsAntiDiagonal) {
  int board[M][N];
  const int v[9] = {0, 0, 1,
                    0, 1, 0,
                    1, 0, 0};
  fill(board, v);
  EXPECT_EQ(parseBoard(board), 1);
}

TEST(ParseBoard, WinByEitherPlayersMarksCounts) {
  // gameLoop stores p+1 so players show up as 2 and 3; any non-zero line wins.
  for (int mark : {1, 2, 3}) {
    int board[M][N];
    initBoard(board, M, N);
    for (int n = 0; n < N; n++) board[1][n] = mark;
    EXPECT_EQ(parseBoard(board), 1) << "mark " << mark;
  }
}

TEST(ParseBoard, MixedLineIsNotAWin) {
  int board[M][N];
  const int v[9] = {1, 1, 2,
                    0, 0, 0,
                    0, 0, 0};
  fill(board, v);
  EXPECT_EQ(parseBoard(board), 0);
}

TEST(ParseBoard, FullBoardWithNoLineIsDraw) {
  int board[M][N];
  const int v[9] = {1, 2, 1,
                    1, 2, 2,
                    2, 1, 1};
  fill(board, v);
  EXPECT_EQ(parseBoard(board), -1);
}

TEST(ParseBoard, WinOnLastMoveBeatsDraw) {
  int board[M][N];
  const int v[9] = {1, 2, 1,
                    2, 1, 2,
                    2, 1, 1};  // full board, main diagonal of 1s
  fill(board, v);
  EXPECT_EQ(parseBoard(board), 1);
}

TEST(ParseBoard, EmptyCellsAloneDoNotCountAsALine) {
  int board[M][N];
  initBoard(board, M, N);
  board[0][0] = 1;
  EXPECT_EQ(parseBoard(board), 0);
}

// ---------- gameLoop ----------

TEST(GameLoop, PlayerOneWinIsAnnouncedAsPlayerOne) {
  int board[M][N];
  initBoard(board, M, N);
  // P1: row 0; P2 plays elsewhere.
  std::string out = play(board, "0 0\n1 0\n0 1\n1 1\n0 2\n");
  EXPECT_TRUE(contains(out, "Player 1 has won!")) << out;
  EXPECT_FALSE(contains(out, "Player 2 has won!")) << out;
}

TEST(GameLoop, PlayerTwoWinIsAnnouncedAsPlayerTwo) {
  int board[M][N];
  initBoard(board, M, N);
  // P2 takes column 2 (0,2 / 1,2 / 2,2).
  std::string out = play(board, "0 0\n0 2\n0 1\n1 2\n1 0\n2 2\n");
  EXPECT_TRUE(contains(out, "Player 2 has won!")) << out;
  EXPECT_FALSE(contains(out, "Player 1 has won!")) << out;
}

TEST(GameLoop, GameStopsImmediatelyAfterWinningMove) {
  int board[M][N];
  initBoard(board, M, N);
  // P1 wins on the 5th move; the extra input must not be consumed as a P2 turn.
  std::string out = play(board, "0 0\n1 0\n0 1\n1 1\n0 2\n2 2\n");
  EXPECT_TRUE(contains(out, "Player 1 has won!")) << out;
  EXPECT_EQ(board[2][2], 0);
}

TEST(GameLoop, DrawEndsTheGame) {
  int board[M][N];
  initBoard(board, M, N);
  // Final board: 1 2 1 / 1 2 2 / 2 1 1 -> no line.
  std::string out = play(board,
                         "0 0\n0 1\n0 2\n1 1\n1 0\n1 2\n2 1\n2 0\n2 2\n");
  EXPECT_TRUE(contains(out, "Draw")) << out;
  EXPECT_FALSE(contains(out, "has won")) << out;
}

TEST(GameLoop, OccupiedCellIsIllegalAndSamePlayerRetries) {
  int board[M][N];
  initBoard(board, M, N);
  // P2 tries (0,0) which P1 already holds, then plays (1,1).
  std::string out = play(board, "0 0\n0 0\n1 1\n");
  EXPECT_TRUE(contains(out, "Illegal move!")) << out;
  EXPECT_NE(board[1][1], 0);
  EXPECT_EQ(board[1][1], board[0][0] + 1);  // P2's mark, not P1's
}

TEST(GameLoop, OutOfRangeMoveIsIllegal) {
  int board[M][N];
  initBoard(board, M, N);
  std::string out = play(board, "3 0\n-1 1\n0 5\n1 1\n");
  EXPECT_TRUE(contains(out, "Illegal move!")) << out;
  EXPECT_NE(board[1][1], 0);
}

TEST(GameLoop, NonNumericInputIsRecovered) {
  int board[M][N];
  initBoard(board, M, N);
  std::string out = play(board, "abc\n1 1\n");
  EXPECT_TRUE(contains(out, "Illegal move!")) << out;
  EXPECT_NE(board[1][1], 0);
}

TEST(GameLoop, EndOfInputTerminatesInsteadOfHanging) {
  int board[M][N];
  initBoard(board, M, N);
  std::string out = play(board, "0 0\n");
  EXPECT_FALSE(contains(out, "has won")) << out;
}
