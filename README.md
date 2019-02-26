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

### Running Results

![Unable to load image](https://github.com/davidjpfeiffer/eight-puzzle/blob/master/Screenshots/running-results-multiple.PNG "Running Results for Multiple Games")

![Unable to load image](https://github.com/davidjpfeiffer/eight-puzzle/blob/master/Screenshots/running-results-single.PNG "Running Results for Single Game")
