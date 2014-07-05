# CMakeLists - Avoid the Bug 3D - Unit Testing
#
# Created on: Aug 10, 2013
#     Author: Dimitri Kourkoulis
 
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT(unittest)

# Boost components
if (WIN32)
FIND_PACKAGE(Boost COMPONENTS unit_test_framework date_time filesystem system REQUIRED)
else()
# It seems that in Linux there is no need to link to the date_time library
FIND_PACKAGE(Boost COMPONENTS unit_test_framework filesystem system REQUIRED)
endif()
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

# Create the executable
ADD_EXECUTABLE(unittest mainTest.cpp gameLogTest.cpp gameLogDebugTest.cpp modelTest.cpp 
 imageTest.cpp ../Model.cpp ../GameLogic.cpp ../WorldObject.cpp ../Character.cpp  
 ../PlayerView.cpp ../GameLog.cpp ../Configuration.cpp configurationTest.cpp 
 ../GameException.cpp ../Image.cpp)

# Link to the required libraries
TARGET_LINK_LIBRARIES(unittest
               ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
               ${Boost_FILESYSTEM_LIBRARIES}
               ${Boost_SYSTEM_LIBRARIES}
)

# Only when building on Windows, also link to the Boost date_time library (see above)
if (WIN32)
TARGET_LINK_LIBRARIES(unittest
		${Boost_DATE_TIME_LIBRARY}
              )
endif()
