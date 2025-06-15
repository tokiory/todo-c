cmake_minimum_required(VERSION 4.0.2)

project(todo-c LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/include/lib)
add_executable(${PROJECT_NAME} src/main.c src/lib/hashmap.c)
