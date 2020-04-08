/*  Name:   Matthew Barton
    ID:     s3732606
    
    My appraoch is mostly centered around my move function in Mazesolver.
    It is looped in the solve method and check if there is an available move.
    If not it backtracks to the previous non-stale breadcrumb. 
    (Backtrack was at one point a seperate function but I found there was more clarity when included in move).
    The loop is exited when the end point is reached.

    The main difficulty I had in the program was tracing segmentation faults.
    In particular when developing the backtrack method, I had an issue that I couldn't isolate.
    In the end I rewrote that section with more care for tracking memory pointers and it worked.
    There was a similar segmentation fault that occured prior to completing the backtrack logic.
    Eventually I realised that because the program was attempting to move but had no where to go,
    it was placing breadcrumbs in the solution until it went out of the memory allocated for the solution.

    Initially I wrote the move method with an if case for each direction.
    But I foudn I was editing four lines of code for any change,
    so I decided to compress it to the one loop that is currently there.
    The arrays with the change in x, y and x, y movement mean that I can handle all of the possiblities at once.

    Printing the directions is handled at the end by comparing the position of breadcrumbs.
    I think this works quite well as it is agnostic of any part of the code except receiving a correct solution.

    Overall I think I have a efficient solution that works consistently.
    I worked a lot at avoiding repetition and having readable code and I think it shows.
    The main point of improvment is the aforementioned arrays
    in the movement function feel like they could be compressed somehow.
    I'm also not completely confident that I'm handling all my memory as efficiently as possible.
    However for both of these I have done my best and can't currently see a way to improve.
*/


#include <iostream>
#include <string>

#include "Types.h"
#include "MazeSolver.h"

// Read a maze from standard input.
void readMazeStdin(Maze maze);

// Print out a Maze to standard output.
void printMazeStdout(Maze maze, Trail* solution);

// Print directions in cardinal directions
void printDirections(Trail* solution);

int main(int argc, char** argv) {
    // Load Maze from stdin
    Maze maze;
    readMazeStdin(maze);

    // Solve maze and get solution
    MazeSolver* solver =    new MazeSolver();
    Trail*      solution =  nullptr;
    solver->solve(maze);
    solution = solver->getSolution();

    // Print Maze to stdout
    printMazeStdout(maze, solution);

    // Print the directio to navigate the maze
    printDirections(solution);

    delete solver;

    return EXIT_SUCCESS;
}

void readMazeStdin(Maze maze) {
    // Uses fixed size for maze
    for (int i = 0; i < MAZE_DIM ; i++) {
        for (int j = 0; j < MAZE_DIM; j++) {
            std::cin >> maze[i][j];
        }
    }
}

void printMazeStdout(Maze maze, Trail* solution) {
    // Put an * at each non-stale breadcrumb's position in the maze (excluding START)
   for (int i = 1; i <= solution->size(); i++) {
      Breadcrumb* currentCrumb = solution->getPtr(i);

      if (!currentCrumb->isStale()) {
         int changeX = currentCrumb->getX();
         int changeY = currentCrumb->getY();
         maze[changeY][changeX] = ROUTE;
      }
   }

    // Print maze
    for (int i = 0; i < MAZE_DIM; i++) {
        for (int j = 0; j < MAZE_DIM; j++) {
            std::cout << maze[i][j];
        }
        std::cout << std::endl;
    }
}

void printDirections(Trail* solution) {
    // Compares the x and y of each breadcrumb to determine movement
    // eg a move of x + 1 is a move down, north
    for (int i = 1; i < solution->size(); i++) {
        Breadcrumb* previousCrumb = solution->getPtr(i);
        Breadcrumb* currentCrumb =  solution->getPtr(i - 1);

        int moveX = previousCrumb->getX() - currentCrumb->getX();
        int moveY = previousCrumb->getY() - currentCrumb->getY();

        if      (moveY == -1) {
            std::cout << "north" << std::endl;
        }
        else if (moveX == 1) {
            std::cout << "east" << std::endl;
        }
        else if (moveY == 1) {
            std::cout << "south" << std::endl;
        }
        else if (moveX == -1) {
            std::cout << "west" << std::endl;
        }
    }
}
