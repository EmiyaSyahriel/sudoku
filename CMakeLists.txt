# CMakeList.txt : CMake project for mini_sudoku, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("mini_sudoku" C)

file(GLOB_RECURSE main_source "app/*.c" "app/*.h")

if(WIN32)
list(APPEND main_source "win32.rc")
endif()

find_package(GLFW3 CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

set(game_libs ${GLFW_LIBRARY} ${GLEW_LIBRARIES_STATIC} ${OPENGL_LIBRARIES})
set(game_incl_dirs ${GLFW_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})

# Add source to this project's executable.
add_executable (sudoku ${main_source})
target_compile_definitions(sudoku PUBLIC -DGLEW_STATIC -DDEBUG -DGAME_LANGUAGE_ID)
target_link_libraries(sudoku PUBLIC ${game_libs})
target_include_directories(sudoku PUBLIC ${game_incl_dirs})

add_executable (sudoku_en ${main_source})
target_compile_definitions(sudoku_en PUBLIC -DGLEW_STATIC -DDEBUG -DGAME_LANGUAGE_EN)
target_link_libraries(sudoku_en PUBLIC ${game_libs})
target_include_directories(sudoku_en PUBLIC ${game_incl_dirs})