cmake_minimum_required(VERSION 3.26)
project(flappyc)
set(CMAKE_C_STANDARD 23)
add_executable(flappyc main.c)


find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)




add_subdirectory(glad)
target_include_directories(flappyc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)

target_link_libraries(flappyc ${OPENGL_LIBRARIES} glfw glad)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "-ggdb -g3")
