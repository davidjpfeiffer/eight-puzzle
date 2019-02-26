# Eight Puzzle

The 8-puzzle is a more simple variation of  the better-known [15-puzzle](https://en.wikipedia.org/wiki/15_puzzle). This game engine uses simple heuristics and complex game engine algorithms to solve the puzzle for any solvable game board. To learn more about the 8-puzzle visit [this site](http://www.aiai.ed.ac.uk/~gwickler/eightpuzzle-uninf.html).

### Getting Started

- Install the [MinGW C++ compiler](https://sourceforge.net/projects/mingw/)
- Clone this repository to your computer
- Configure the game engine settings (optional)
- Run the `compile.bat` script to create the executable program
- Run the newly created `main.exe` file from the command line

### Game Engine Settings

You can configure the settings for the game engine by modifying the `gameEngineSettings.h` file in the `Game` directory. You must recompile the program after making changes. The following settings may be changes from this file:

- Number of games to be played
- The difficulty of the boards to be solved (more difficult boards require more moves to solve)
- Whether to show the step-by-step moves for each solution
- Which algorithm should be used as a heuristic to find a solution

### How It Works

The algorithms use heuristics to quantify how good or bad a given game state is; smaller values indicate that a game state is almost solved, while larger values indicate that a game state is no where near being solved.

The game engine starts with a game state that needs to be solved. The engine recursively calculates the valid moves from the current game state to subsequent game states effectively building a tree of all possible game states.

Duplicate game states are not considered, an optimization which allows us to use an exhaustive search. This optimization is implemented using a map which keeps track of which games states have already been visited.

The solution state is then found within the tree and a path from the root node to the solution node can be easily found; this path represents the moves that must be made to transform the initial game state to the solved game state.

### Running Results

![Unable to load image](https://github.com/davidjpfeiffer/eight-puzzle/blob/master/Screenshots/running-results-multiple.PNG "Running Results for Multiple Games")

![Unable to load image](https://github.com/davidjpfeiffer/eight-puzzle/blob/master/Screenshots/running-results-single.PNG "Running Results for Single Game")
