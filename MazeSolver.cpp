
#include "MazeSolver.h"


MazeSolver::MazeSolver() {
   solution = new Trail();
}

MazeSolver::~MazeSolver() {
    delete solution;
}

// Searches maze for target and return it's coordinates in an array
void find(Maze maze, char target, int* x, int* y);

// Checks in order of north, east, south, west and moves to the first open non-breadcrumbed space
// Returns true if there is a valid location, false if there is not
void move(Maze maze, Trail* solution, int* x, int* y);

// Called there are no empty spots to move to
// Retraces it's step over previous breadcrumbs and marks them as stale
// Until it reaches a breadcrumb with a new movement option
void backtrack(Maze maze, Trail* solution, int* x, int* y);

void MazeSolver::solve(Maze maze) {
   // Find and move to the start location in the maze
   find(maze, START, &x, &y);
   
   // Move until the exit is found
   while (maze[y][x] != END) {
      // Add a breadcrumb at every location we move to without a breadcrumb
      if (!solution->contains(x, y)) {
         solution->addCopy(new Breadcrumb(x, y, false));
      }
      move(maze, solution, &x, &y);
   }
}

Trail* MazeSolver::getSolution() {
   Trail* solutionCopy = new Trail;
   for (int i = 0; i <= solution->size(); i <  i++) {
      Breadcrumb* crumb = solution->getPtr(i);

      if (!crumb->isStale()) {
         solutionCopy->addCopy(new Breadcrumb(crumb->getX(), crumb->getY(), crumb->isStale()));
      }
   }


   return solutionCopy;
}

void find(Maze maze, char target, int* x, int* y) {
   for (int i = 0; i < MAZE_DIM; i++){
      for (int j = 0; j < MAZE_DIM; j++){
         if (maze[i][j] == target) {
            *y = i;
            *x = j;
         }
      }
   }
}

void move(Maze maze, Trail* solution, int* x, int* y) {
// Puts the character in each cardinal direction of the location in an array
   char north =   maze[*y-1]  [*x];
   char east =    maze[*y]    [*x+1];
   char south =   maze[*y+1]  [*x];
   char west =    maze[*y]    [*x-1];
   char directions[] = {north, east, south, west};

   // Puts movement required for each cardinal direction in a 2D array
   int moveNorth[] =   {0, -1};
   int moveEast[] =    {1, 0};
   int moveSouth[] =   {0, 1};
   int moveWest[] =    {-1, 0};
   int* moveDirections[] = {moveNorth, moveEast, moveSouth, moveWest};

   // Checks if each cardinal direction is either empty or the end of the maze
   // If that spot also doesn't contain an breadcrumb then move the location to the spot
   for (int i = 0; i < 4; i++){
      int moveX = *x + moveDirections[i][0];
      int moveY = *y + moveDirections[i][1];

      if ((directions[i] == OPEN 
      || directions[i] == END) 
      && !solution->contains(moveX, moveY)) {
         *x = moveX;     
         *y = moveY;
         return;
      }
   }

   // Set the current breadcrumb to stale then moves to the last non-stale breadcrumb
   int size = solution->size();
   Breadcrumb* currentCrumb =    solution->getPtr(size);
   Breadcrumb* previousCrumb =   solution->getPtr(size - 1);

   for (int i = 0; currentCrumb->isStale(); i++) {
      currentCrumb =    solution->getPtr(size - i);
      previousCrumb =   solution->getPtr(size - i -1);
   }

   if (!currentCrumb->isStale()) {
      currentCrumb->setStale(true);
      *x = previousCrumb->getX();
      *y = previousCrumb->getY();
   }
}
