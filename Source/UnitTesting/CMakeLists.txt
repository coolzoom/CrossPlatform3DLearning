CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT(unittest)
FIND_PACKAGE(Boost COMPONENTS unit_test_framework REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
LINK_LIBRARIES(
               ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
              )
ADD_EXECUTABLE(unittest mainTest.cpp ../GameCharacter.cpp ../GameCharacter.h)


