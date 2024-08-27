cmake_minimum_required(VERSION 3.20)

# Project name and version
project(meddle VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

# Do optimization
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")

# Set PIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Add the library
add_library(meddle-c SHARED
    meddle.c
    # include/LibMeddle.h
)

add_library(meddle-cpp SHARED
    meddle.cpp
    # include/LibMeddle.h
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

add_executable(meddle-test-c
    meddle-test.c
)
target_link_libraries(meddle-test-c PRIVATE meddle-c)
set_target_properties(meddle-test-c PROPERTIES
    INSTALL_RPATH "\$ORIGIN/../lib"
)

add_executable(meddle-test-cpp
    meddle-test.cpp
)
target_link_libraries(meddle-test-cpp PRIVATE meddle-cpp)
set_target_properties(meddle-test-cpp PROPERTIES
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

install(TARGETS meddle-test-c meddle-test-cpp
    RUNTIME DESTINATION bin
)

# set(CMAKE_INSTALL_DO_STRIP TRUE)
