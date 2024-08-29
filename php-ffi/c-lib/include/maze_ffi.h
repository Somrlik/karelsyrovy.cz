typedef enum MazeTile {
    MAZE_TILE_WALL = 0,
    MAZE_TILE_PATH = 1,
} MazeTile;

typedef struct Maze {
    int width;
    int height;
    MazeTile* layout;
} Maze;

typedef struct MazeSolution {
} MazeSolution;

bool mazeToString(Maze, char* buffer, unsigned int bufferLen);

bool generateMaze(int width, int height, Maze* maze);

bool solveMaze(Maze, MazeSolution*);
