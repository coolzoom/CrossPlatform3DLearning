cmake_minimum_required (VERSION 2.7)
project (test)
include_directories ("/usr/include")
include_directories ("/usr/include/SDL")
link_directories("/usr/lib/x86_64-linux-gnu")
link_libraries (SDL)
add_executable (test main.cpp)



