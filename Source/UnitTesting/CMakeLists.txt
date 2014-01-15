CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT(unittest)
if (WIN32)
FIND_PACKAGE(Boost COMPONENTS unit_test_framework date_time REQUIRED)
else()
FIND_PACKAGE(Boost COMPONENTS unit_test_framework REQUIRED)
endif()

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

LINK_LIBRARIES(
               ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

if (WIN32)
LINK_LIBRARIES(
		${Boost_DATE_TIME_LIBRARY}
              )
endif()

ADD_EXECUTABLE(unittest mainTest.cpp gameLogTest.cpp gameLogDebugTest.cpp modelTest.cpp 
 ../Model.cpp ../GameLogic.cpp
 ../WorldObject.cpp ../Character.cpp
 ../PlayerView.cpp ../GameLog.cpp)


