CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(LIBDYNAMIXEL)

SET(CMAKE_C_FLAGS "-I ${CMAKE_CURRENT_SOURCE_DIR} -g -Wall")
MESSAGE(STATUS "libdynamixel C_FLAGS: ${CMAKE_C_FLAGS}")

ADD_LIBRARY(dynamixel instruction.cpp packet.cpp status.cpp usb2dynamixel.cpp)

IF (WITH_SHARED)
  ADD_LIBRARY(dynamixel_shared SHARED instruction.cpp packet.cpp status.cpp usb2dynamixel.cpp)
ENDIF(WITH_SHARED)

INSTALL (FILES dynamixel.hpp
  DESTINATION include/dynamixel/
)

INSTALL (TARGETS dynamixel
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)


