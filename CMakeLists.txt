cmake_minimum_required(VERSION 3.0.0)
project(basicGames VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

add_executable(basicGames
    src/main.cpp 
    src/glad/glad.c 
)

target_link_libraries(basicGames
    glfw
)