
#ifndef COSC_ASS_ONE_TYPES
#define COSC_ASS_ONE_TYPES

// Orientation codes
#define WALL        '='
#define OPEN        '.'
#define ROUTE       '*'

#define MAZE_DIM                20
#define TRAIL_ARRAY_MAX_SIZE    (MAZE_DIM * MAZE_DIM)

// A 2D array to represent the maze or observations
// REMEMBER: in a maze, the location (x,y) is found by maze[y][x]!
typedef char Maze[MAZE_DIM][MAZE_DIM];


#endif // COSC_ASS_ONE_TYPES
