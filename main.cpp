
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
    MazeSolver* solver = new MazeSolver();
    Trail* solution = nullptr;
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
    // ASSUME THE MAZE IS A FIXED SIZE (20X20).
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
         std::cout << changeX << changeY << std::endl;
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

void printDirections(Trail* solution) {
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
