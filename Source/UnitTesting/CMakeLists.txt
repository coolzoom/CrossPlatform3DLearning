CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT(unittest)
FIND_PACKAGE(Boost COMPONENTS unit_test_framework REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
LINK_LIBRARIES(
               ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
              )
ADD_EXECUTABLE(unittest mainTest.cpp gameLogTest.cpp modelTest.cpp ../Model.cpp ../Model.h ../GameLogic.h ../GameLogic.cpp
 ../WorldObject.h ../WorldObject.cpp ../Character.h ../Character.cpp ../PlayerView.h
 ../PlayerView.cpp ../Renderer.h ../Renderer.cpp ../GameLog.h ../GameLog.cpp)


