cmake_minimum_required (VERSION 2.8)
project (game)

Find_Package(SDL REQUIRED)

if (NOT SDL_FOUND)
	message( FATAL ERROR "SDL not found!")
endif(NOT SDL_FOUND)

include_directories(${SDL_INCLUDE_DIR})

link_libraries(
	${SDL_LIBRARY}
)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

add_executable (game main.cpp)

target_link_libraries(game ${OPENGL_LIBRARIES}) 
