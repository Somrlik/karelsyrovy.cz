#include <maze.h>
#include <random.h>
#include <gtest/gtest.h>
#include "./utils.h"

TEST(Mazer, MazeGenerator) {
    EXPECT_FALSE(generateMaze(10, 10, nullptr));

    Maze maze = {0, 0, nullptr};
    const unsigned int bufferSize = 1024 * 1024;
    char* buffer = (char*)malloc(bufferSize);

    EXPECT_FALSE(generateMaze(-1, -1, &maze));
    EXPECT_FALSE(generateMaze(0, 0, &maze));
    EXPECT_FALSE(generateMaze(2, 2, &maze));
    EXPECT_TRUE(generateMaze(3, 3, &maze));
    EXPECT_TRUE(mazeToString(maze, buffer, bufferSize));
    // This is the only possible option
    EXPECT_STREQ(buffer, "###\n# #\n###\n");

    randomIntReset();
    EXPECT_TRUE(generateMaze(10, 10, &maze));
    EXPECT_TRUE(mazeToString(maze, buffer, bufferSize));
    EXPECT_STREQ(buffer, "##########\n#     # ##\n# ### # ##\n# # # # ##\n# # # # ##\n# #   # ##\n### ### ##\n#       ##\n##########\n##########\n");

    randomIntReset();
    EXPECT_TRUE(generateMaze(50, 50, &maze));
    EXPECT_EQ(maze.width, 50);
    EXPECT_EQ(maze.height, 50);
    EXPECT_TRUE(mazeToString(maze, buffer, bufferSize));
    EXPECT_TRUE(FileContentsEqual("maze_50x50.txt", buffer));

    randomIntReset();
    EXPECT_TRUE(generateMaze(100, 5, &maze));
    EXPECT_EQ(maze.width, 100);
    EXPECT_EQ(maze.height, 5);
    EXPECT_TRUE(mazeToString(maze, buffer, bufferSize));
    EXPECT_TRUE(FileContentsEqual("maze_100x5.txt", buffer));

    free(buffer);
}
