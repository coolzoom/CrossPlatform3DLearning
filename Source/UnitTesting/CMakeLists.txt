CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT(unittest)
FIND_PACKAGE(Boost COMPONENTS unit_test_framework date_time REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
LINK_LIBRARIES(
               ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
               ${Boost_DATE_TIME_LIBRARY}
              )
ADD_EXECUTABLE(unittest mainTest.cpp gameLogTest.cpp gameLogDebugTest.cpp modelTest.cpp 
 ../Model.cpp ../GameLogic.cpp
 ../WorldObject.cpp ../Character.cpp
 ../PlayerView.cpp ../GameLog.cpp)


