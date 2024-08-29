#ifndef MEDDLE_MAZE_H
#define MEDDLE_MAZE_H

#if !__cplusplus
#include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define OUTPUT_PARAM

#define MAZE_MIN_WIDTH 3
#define MAZE_MIN_HEIGHT 3

typedef enum MazeTile {
    MAZE_TILE_WALL = 0,
    MAZE_TILE_PATH = 1,
    /** @internal @deprecated */
    MAZE_TILE_VISITED = 99,
} MazeTile;

typedef struct Maze {
    int width;
    int height;
    MazeTile* layout;
} Maze;

typedef struct MazeSolution {
    // TODO: Somehow do steps
} MazeSolution;

bool mazeToString(Maze, OUTPUT_PARAM char* buffer, unsigned int bufferLen);

bool generateMaze(int width, int height, OUTPUT_PARAM Maze* maze);

bool solveMaze(Maze, OUTPUT_PARAM MazeSolution*);

#ifdef __cplusplus
}
#endif

#endif
