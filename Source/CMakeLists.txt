# CMakeLists - Avoid the Bug 3D
#
# Created on: Aug 10, 2013
#     Author: Dimitri Kourkoulis

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(game)

# Boost
IF(WIN32)
FIND_PACKAGE(Boost COMPONENTS date_time filesystem system REQUIRED)
ELSE()
# It seems that in Linux there is no need to link to the date_time library
FIND_PACKAGE(Boost COMPONENTS filesystem system REQUIRED)
ENDIF()
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

# SDL (Simple DirectMedia Layer)
FIND_PACKAGE(SDL REQUIRED)
IF(NOT SDL_FOUND)
	MESSAGE(FATAL ERROR "SDL not found!")
ENDIF(NOT SDL_FOUND)
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})

# OpenGL
FIND_PACKAGE(OpenGL REQUIRED)
INCLUDE_DIRECTORIES(${OpenGL_INCLUDE_DIRS})
LINK_DIRECTORIES(${OpenGL_LIBRARY_DIRS})
ADD_DEFINITIONS(${OpenGL_DEFINITIONS})
# This is here because I have read about a "bug", due to which
# there is no problem reported when OpenGL is not found.
IF(NOT OPENGL_FOUND)
    MESSAGE(ERROR " OPENGL not found!")
ENDIF(NOT OPENGL_FOUND)

# GLM
IF(WIN32)
FIND_PACKAGE(GLM REQUIRED)
INCLUDE_DIRECTORIES(${GLM_INCLUDE_DIRS})
ENDIF()

# GLEW (OpenGL Extension Wrangler Library)
FIND_PACKAGE(GLEW REQUIRED)
IF(NOT GLEW_FOUND)
   MESSAGE(ERROR "GLEW not found!")
ENDIF(NOT GLEW_FOUND)
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_PATH})
MESSAGE(${GLEW_LIBRARIES})

# libpng
FIND_PACKAGE(PNG REQUIRED)
INCLUDE_DIRECTORIES(${PNG_INCLUDE_DIRS})
ADD_DEFINITIONS(${PNG_DEFINITIONS})

# Create the executable
ADD_EXECUTABLE(game main.cpp GameLog.cpp Model.cpp GameLogic.cpp
 WorldObject.cpp Character.cpp 
 PlayerView.cpp Renderer.cpp RendererOpenGL14.cpp RendererOpenGL33.cpp
 RendererOpenGL21.cpp GameException.cpp Configuration.cpp Image.cpp
 )

# Link to the required libraries
TARGET_LINK_LIBRARIES(game ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL_LIBRARY} ${Boost_FILESYSTEM_LIBRARIES}
               ${Boost_SYSTEM_LIBRARIES} ${PNG_LIBRARIES}) 

# Only when building on Windows, also link to the Boost date_time library (see above)
if (WIN32)
TARGET_LINK_LIBRARIES(game
               ${Boost_DATE_TIME_LIBRARY}
              )
ENDIF()

# Unit tests compiled separately
ADD_SUBDIRECTORY(UnitTesting)