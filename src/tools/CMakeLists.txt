CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(tools)

find_package (Boost 1.55.0 REQUIRED COMPONENTS system filesystem)

include_directories (SYSTEM ${Boost_INCLUDE_DIR})
INCLUDE_DIRECTORIES(../)
link_directories (${Boost_LIBRARY_DIRS})
link_directories(../dynamixel)


ADD_EXECUTABLE(tool dynamixel.cpp)
target_link_libraries (tool ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(tool dynamixel)

