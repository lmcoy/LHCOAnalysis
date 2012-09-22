cmake_minimum_required (VERSION 2.6)

project (LHCOAnalysis)

include_directories(.)
set(CMAKE_CXX_FLAGS "-O2 -ggdb -Wall -Wextra -fmessage-length=0 -std=c++0x")
add_subdirectory (src)
