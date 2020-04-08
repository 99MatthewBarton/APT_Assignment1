
#include <iostream>
#include <string>

#include "Types.h"
#include "MazeSolver.h"

// Helper test functions
void testBreadcrumb();
void testTrail();

// Read a maze from standard input.
void readMazeStdin(Maze maze);

// Print out a Maze to standard output.
void printMazeStdout(Maze maze, Trail* solution);

int main(int argc, char** argv) {
    // Load Maze from stdin
    Maze maze;
    readMazeStdin(maze);

    // Solve using MazeSolver
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    MazeSolver* solver = new MazeSolver();
    Trail* solution = nullptr;
    solver->solve(maze);
    solution = solver->getSolution();

    // Print Maze to stdout
    printMazeStdout(maze, solution);

    delete solver;

    return EXIT_SUCCESS;
}

void readMazeStdin(Maze maze) {
    // ASSUME THE MAZE IS A FIXED SIZE (20X20).
    for (int i = 0; i < MAZE_DIM ; i++) {
        for (int j = 0; j < MAZE_DIM; j++) {
            std::cin >> maze[i][j];
        }
    }
}

void printMazeStdout(Maze maze, Trail* solution) {
    // Put an * at each non-stale breadcrumb's position in the maze
   for (int i = 0; i < solution->size(); i++) {
      Breadcrumb* currentCrumb = solution->getPtr(solution->size()-i);
      if (!currentCrumb->isStale()) {
         int changeX = currentCrumb->getX();
         int changeY = currentCrumb->getY();
         maze[changeY][changeX] = ROUTE;
      }
   }

    for (int i = 0; i < MAZE_DIM; i++) {
        for (int j = 0; j < MAZE_DIM; j++) {
            std::cout << maze[i][j];
        }
        std::cout << std::endl;
    }
}
