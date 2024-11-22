cmake_minimum_required(VERSION 3.20)

# Project name and version
project(meddle VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

# Set PIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Add the library
add_library(meddle-c SHARED
    meddle.c
    random.c
    maze_to_string.c
    maze_generator.c
    maze_solver.c
    abi_interop.c
)

add_library(meddle-cpp SHARED
    meddle.cpp
)

target_include_directories(meddle-c PUBLIC include)
target_include_directories(meddle-cpp PUBLIC include)

# Optionally, set the output directory for the built library
set_target_properties(meddle-c PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
set_target_properties(meddle-cpp PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

add_executable(maze-debug-c
    maze_debug.c
    abi_interop.c
)
target_link_libraries(maze-debug-c PRIVATE meddle-c)
set_target_properties(maze-debug-c PROPERTIES
    INSTALL_RPATH "\$ORIGIN/../lib"
)

# Install the library
install(TARGETS meddle-c meddle-cpp
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

# Install the header files
install(DIRECTORY include/
    DESTINATION include
)

install(TARGETS maze-debug-c
    RUNTIME DESTINATION bin
)

# set(CMAKE_INSTALL_DO_STRIP TRUE)

enable_testing()

# Testing using googletest
set(INSTALL_GTEST OFF)
set(GOOGLETEST_HEAD 03597a01ee50ed33e9dfd640b249b4be3799d395)
include(FetchContent)
FetchContent_Declare(
        googletest
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/google/googletest/archive/${GOOGLETEST_HEAD}.zip
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS test/*.cpp)

add_executable(meddle-c-googletest ${TEST_FILES})
target_sources(meddle-c-googletest PRIVATE ${TEST_FILES})

target_include_directories(meddle-c-googletest PRIVATE include)

target_link_libraries(
        meddle-c-googletest
        GTest::gtest_main
        meddle-c
)

include(GoogleTest)
gtest_discover_tests(meddle-c-googletest)

add_custom_command(
    TARGET meddle-c-googletest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/test/resources $<TARGET_FILE_DIR:meddle-c-googletest>/resources
    DEPENDS meddle-c-googletest
)
