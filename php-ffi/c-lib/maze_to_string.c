#include <meddle.h>
#include <stdio.h>
#include <random.h>
#include <stdbool.h>
#include <maze.h>

// TODO: Implement solution printing
bool mazeToString(const Maze maze, OUTPUT_PARAM char *buffer, const unsigned int bufferLen) {
    if (maze.width < MAZE_MIN_WIDTH || maze.height < MAZE_MIN_HEIGHT) {
        return false;
    }

    size_t requiredBufferSize = sizeof(char) * (maze.width + 1) * maze.height + 1;
    if (bufferLen < requiredBufferSize) {
        return false;
    }

    // Allocate every row  + \n, times height + \0
    for (int row = 0; row < maze.height; row++) {
        for (int col = 0; col < maze.width; col++) {
            MazeTile tile = maze.layout[row * maze.width + col];
            char c = '?';
            if (tile == MAZE_TILE_VISITED) {
                c = '.';
            } else if (tile == MAZE_TILE_WALL) {
                c = '#';
            } else if (tile == MAZE_TILE_PATH) {
                c = ' ';
            }
            buffer[row * (maze.width + 1) + col] = c;
        }
        buffer[row * (maze.width + 1) + maze.width] = '\n';
    }
    buffer[(maze.width + 1) * maze.height] = '\0';
    return true;
}

bool mazeToStringWithSolution(OUTPUT_PARAM char *buffer, const unsigned int bufferLen, const Maze maze, const MazeSolution mazeSolution) {
    return false;
}