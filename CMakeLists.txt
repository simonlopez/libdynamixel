CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(dynamixel)

ADD_SUBDIRECTORY(src/dynamixel)

IF (WITH_DEMOS)
  ADD_SUBDIRECTORY(src/demos)
ENDIF (WITH_DEMOS)

IF (WITH_TOOLS)
  ADD_SUBDIRECTORY(src/tools)
ENDIF (WITH_TOOLS)
