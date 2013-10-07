cmake_minimum_required (VERSION 2.8)
project (test)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
link_libraries(
               ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
              )
add_executable (test main.cpp)


