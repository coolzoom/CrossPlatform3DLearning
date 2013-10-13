cmake_minimum_required (VERSION 2.8)
project (unittest)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_libraries(
               ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
              )
add_executable (unittest main.cpp)


