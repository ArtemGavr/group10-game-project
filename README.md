# _Cybergame Name_

## Authors:
| Username        | Name               |
|-----------------|--------------------|
| amelie-major 	  | Amelie Major       |
| ArtemGavr 	  | Artem Gavryushenko |
| PhoebeJohnstone | Phoebe Johnstone   |
| cshumate2114    | Connor Shumate     |

## Win Conditions:
_Describe the win conditions for either player (i.e. the × or ○ player)_

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
