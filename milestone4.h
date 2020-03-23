/*
 * These are some sample functions to help you dynamically allocate
 *  memory for a generic 2D Maze.
 */

Maze make_maze(const int rows, const int cols) {
   Maze maze = nullptr;

   if (rows >= 0 && cols >= 0) {
      maze = new char*[rows];
      for (int i = 0; i != rows; ++i) {
         maze[i] = new char[cols];
      }
   }

   return maze;
}


void delete_maze(Maze maze, int rows, int cols) {
   if (rows >= 0 && cols >= 0) {
      for (int i = 0; i != rows; ++i) {
         delete maze[i];
      }
      delete maze;
   }

   return;
}