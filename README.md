# _Tic Tac Toe_

## Authors:
| Username        | Name               |
|-----------------|--------------------|
| amelie-major 	  | Amelie Major       |
| ArtemGavr 	  | Artem Gavryushenko |
| PhoebeJohnstone | Phoebe Johnstone   |
| cshumate2114    | Connor Shumate     |

## Win Conditions:
A player wins by placing three of their symbols in a straight line on the 3x3 game board.

There are three possible ways to win:

- **Horizontal:** Three matching symbols in any row
- **Vertical:** Three matching symbols in any column
- **Diagonal:** Three matching symbols diagonally across the board (from corner to corner)

The game checks for a winning line after every valid move.

- If a player achieves three matching symbols in a line, they win and the game ends.
- If all nine cells are filled and neither player has won, the game ends in a draw.

## Build Instructions:
### Test Mode:
The Debug build compiles the game with debugging information and enables automated tests using GoogleTest.

Run the following commands from the root directory of the project:

cmake -S . -B build-test -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON
cmake --build build-test
ctest --test-dir build-test --output-on-failure

### Release Build:

The Release build compiles an optimised version of the game without automated tests.

Run:

cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF
cmake --build build-release

### Running the Game:
Once the Release build has completed, run the executable.

**Windows (PowerShell):**

.\build-release\game.exe

**Linux/macOS:**

./build-release/game
