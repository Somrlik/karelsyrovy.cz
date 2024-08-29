#include <stdio.h>
#include <maze.h>
#include <malloc.h>

int main() {
    Maze maze = {0, 0, NULL};
    generateMaze(3, 3, &maze);

    char* buffer = malloc(1024 * 1024);
    mazeToString(maze, buffer, 1024 * 1024);
    printf("%s", buffer);

    return 0;
}