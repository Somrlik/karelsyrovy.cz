#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <maze.h>
#include <random.h>

#include "./require_nonnull.h"

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct WallStack {
    int size;
    int maxSize;
    Point* theStack;
} WallStack;

typedef enum TileVisited {
    TILE_NOT_VISITED = 0,
    TILE_VISITED = 99,
} TileVisited;

typedef struct MazeVisited {
    int width;
    int height;
    TileVisited* layout;
} MazeVisited;

WallStack wallStack = {0, 0, NULL};

void pushToWallStack(const Point point) {
    if (wallStack.size + 1 > wallStack.maxSize) {
        const int newMaxSize = (wallStack.maxSize + 1) * 2;
        wallStack.theStack = realloc(wallStack.theStack, sizeof(Point) * newMaxSize);
        require_nonnull(wallStack.theStack);
        wallStack.maxSize = newMaxSize;
    }

    wallStack.theStack[wallStack.size] = point;
    wallStack.size++;
}

bool popFromWallStack(OUTPUT_PARAM Point* point) {
    if (wallStack.size == 0) {
        return false;
    }

    *point = wallStack.theStack[wallStack.size - 1];
    wallStack.size--;
    return true;
}

void freeWallStack() {
    free(wallStack.theStack);
    wallStack.theStack = NULL;
    wallStack.maxSize = 0;
    wallStack.size = 0;
}

#define inBetween(min, value, max) (((min) < (value) && (value) < (max)))

bool hasAnyNeighboursNotVisited(Point *point, MazeVisited *visited, OUTPUT_PARAM Point *unvisited, unsigned int *unvisitedCount) {
    // Check bounding box
    const bool topAvailable =
            inBetween(0, point->x    , visited->width - 1) &&
            inBetween(0, point->y + 2, visited->height - 1);
    const bool rightAvailable =
            inBetween(0, point->x + 2, visited->width - 1) &&
            inBetween(0, point->y    , visited->height - 1);
    const bool bottomAvailable =
            inBetween(0, point->x    , visited->width - 1) &&
            inBetween(0, point->y - 2, visited->height - 1);
    const bool leftAvailable =
            inBetween(0, point->x - 2, visited->width - 1) &&
            inBetween(0, point->y    , visited->height - 1);

    // Check which ones have been visited
    *unvisitedCount = 0;
    if (topAvailable && visited->layout[point->x + visited->width * (point->y + 2)] != TILE_VISITED) {
        unvisited[*unvisitedCount].x = point->x;
        unvisited[*unvisitedCount].y = point->y + 2;
        (*unvisitedCount)++;
    }

    if (rightAvailable && visited->layout[(point->x + 2) + visited->width * point->y] != TILE_VISITED) {
        unvisited[*unvisitedCount].x = point->x + 2;
        unvisited[*unvisitedCount].y = point->y;
        (*unvisitedCount)++;
    }

    if (bottomAvailable && visited->layout[point->x + visited->width * (point->y - 2)] != TILE_VISITED) {
        unvisited[*unvisitedCount].x = point->x;
        unvisited[*unvisitedCount].y = point->y - 2;
        (*unvisitedCount)++;
    }
    if (leftAvailable && visited->layout[(point->x - 2) + visited->width * point->y] != TILE_VISITED) {
        unvisited[*unvisitedCount].x = point->x - 2;
        unvisited[*unvisitedCount].y = point->y;
        (*unvisitedCount)++;
    }

    return *unvisitedCount != 0;
}

/**
 * Very slow maze generation algorithm
 *
 * @see https://en.wikipedia.org/wiki/Maze_generation_algorithm#Iterative_implementation_(with_stack)
 * @param width
 * @param height
 * @param maze
 * @return true if successfully generated, false otherwise
 */
bool generateMaze(const int width, const int height, OUTPUT_PARAM Maze* maze) {
    if (width < MAZE_MIN_WIDTH || height < MAZE_MIN_HEIGHT) {
        return false;
    }

    if (maze == NULL) {
        return false;
    }

    // Free the old layout, reasonably should be nullptr
    free(maze->layout);
    maze->width = width;
    maze->height = height;

    const unsigned long memorySize = sizeof(enum MazeTile) * width * height;
    maze->layout = malloc(memorySize);
    require_nonnull(maze->layout);
    MazeVisited visited = {width, height, malloc(memorySize)};
    require_nonnull(visited.layout);

    // 0. Start with all walls
    memset(maze->layout, MAZE_TILE_WALL, memorySize);
    memset(visited.layout, TILE_NOT_VISITED, memorySize);

    // 1. Choose the initial cell, mark it as visited and push it to the stack
    Point start = {randomIntBetween(1, width - 2), randomIntBetween(1, height - 2)};
    // Align to odd number to prevent 2-thick borders
    start.x = start.x % 2 == 1 ? start.x : start.x + 1;
    start.y = start.y % 2 == 1 ? start.y : start.y + 1;
    maze->layout[start.x + width * start.y] = MAZE_TILE_PATH;
    visited.layout[start.x + width * start.y] = TILE_VISITED;
    pushToWallStack(start);

    Point* unvisitedNeighbours = malloc(sizeof(Point) * 4);
    require_nonnull(unvisitedNeighbours);

    // 2. While the stack is not empty
    while (wallStack.size != 0) {
        // 2.1. Pop a cell from stack and make it a current cell
        Point current = {-1, -1};
        unsigned int unvisitedCount;
        popFromWallStack(&current); // TODO: Maybe check return value
        // 2.2. If the current cell has any neighbors which have not been visited
        if (hasAnyNeighboursNotVisited(&current, &visited, unvisitedNeighbours, &unvisitedCount)) {
            // 2.2.1 Push the current cell to the stack
            pushToWallStack(current);

            // 2.2.2 Choose one of the unvisited neighbors
            unsigned int idx = randomIntBetween(0, (int)unvisitedCount - 1);
            const Point chosenNeighbor = unvisitedNeighbours[idx];
            const Point newPath = {(current.x + chosenNeighbor.x) / 2, (current.y + chosenNeighbor.y) / 2};

            // 2.2.3 Remove the wall between the current cell and the chosen cell
            maze->layout[chosenNeighbor.x + width * chosenNeighbor.y] = MAZE_TILE_PATH;
            maze->layout[newPath.x + width * newPath.y] = MAZE_TILE_PATH;
            // 2.2.4 Mark the chosen cell as visited and push to the stack
            visited.layout[chosenNeighbor.x + width * chosenNeighbor.y] = TILE_VISITED;
            visited.layout[newPath.x + width * newPath.y] = TILE_VISITED;
            pushToWallStack(chosenNeighbor);
        }
    }

    free(unvisitedNeighbours);
    free(visited.layout);
    freeWallStack();

    return true;
}