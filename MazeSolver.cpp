
#include "MazeSolver.h"


MazeSolver::MazeSolver() {
   // TODO
}

MazeSolver::~MazeSolver() {
    delete solution;
}

// Searches maze for target and return it's coordinates in an array
void find(Maze maze, char target, int* location);

// Checks in order of north, east, south, west and moves to the first open non-breadcrumbed space
// Returns true if there is a valid location, false if there is not
bool move(Maze maze, int* location);

/*
repeat
   if The trail has no bredcrumb for our current location, b then
      Add a breadcrumb for b to the end of the trail, that is T.addback(b)
   end
   // Look for a place to go next
   // In order of north, east, south, west from b find the first location l, such that:
   if l is empty and we havent left a breadcrumb in the trail T then
      Move from b to l. That is, b = l
   else
      // We need to Backtrack, as there is no-where we can go
      Mark b (current breadcrumb) as “stale”. (Make sure to update this within T)
      Find the last good breadcrumb in the Trail T, call it bgood.
      Go to this breadcrumb, that is b = bgood.
   end
until We reach the end, that is b == E 
*/

void MazeSolver::solve(Maze maze) {
   // Finds the start location in the maze
   find(maze, START, location);

   // TEST
   std::cout << "TEST - x: " << location[1] << " y: " << location[0] << std::endl;
   
   // Move until the exit is found
   while (maze[location[0]][location[1]] != END) {
      if (!move(maze, location)) {
         // backtrack
      }
   std::cout << "TEST - x: " << location[1] << " y: " << location[0] << std::endl;
   }
}

Trail* MazeSolver::getSolution() {
   // TODO
   return nullptr;
}

void find(Maze maze, char target, int* location) {
   for (int i = 0; i < MAZE_DIM; i++){
      for (int j = 0; j < MAZE_DIM; j++){
         if (maze[i][j] == target) {
            location[0] = i;
            location[1] = j;
         }
      }
   }
}

bool move(Maze maze, int* location) {
   int y = location[0];
   int x = location[1];

   char north = maze[y][x+1];
   char east = maze[y+1][x];
   char south = maze[y][x-1];
   char west = maze[y-1][x];

   char directions[] = {north, east, south, west};

   // TODO: Add breadcrumb check
   for (char direction : directions){
      if (direction == OPEN || direction == END) {
         location[1]++;
         return true;
      }
   }
   // Check north
   if (north == OPEN || north == END) {
      location[1]++;
      return true;
   }

   // Check east
   else if (east == OPEN || east == END) {
      location[0]++;
      return true;
   }

   // Check south
   else if ((south == OPEN) || south == END) {
      location[1]--;
      return true;
   }

   // Check west
   else if ((west == OPEN) || west == END) {
      location[0]--;
      return true;
   }
   return false;
}
