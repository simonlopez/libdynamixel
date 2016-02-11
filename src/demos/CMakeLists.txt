CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(demos)

INCLUDE_DIRECTORIES(../)
link_directories(../dynamixel)

ADD_EXECUTABLE(demo1_stand_up demo1_stand_up.cpp)
TARGET_LINK_LIBRARIES(demo1_stand_up dynamixel)

ADD_EXECUTABLE(demo2_wriggle demo2_wriggle.cpp)
TARGET_LINK_LIBRARIES(demo2_wriggle dynamixel)

ADD_EXECUTABLE(demo3_static_walk demo3_static_walk.cpp monitor.cpp)
TARGET_LINK_LIBRARIES(demo3_static_walk dynamixel)

ADD_EXECUTABLE(demo3_static_walk_pause demo3_static_walk_pause.cpp monitor.cpp)
TARGET_LINK_LIBRARIES(demo3_static_walk_pause dynamixel)

ADD_EXECUTABLE(demo4_sinusoid_walk demo4_sinusoid_walk.cpp actuator.cpp monitor.cpp)
TARGET_LINK_LIBRARIES(demo4_sinusoid_walk dynamixel)

ADD_EXECUTABLE(demo5_discrete_sinusoid_walk demo5_discrete_sinusoid_walk.cpp actuator.cpp monitor.cpp)
TARGET_LINK_LIBRARIES(demo5_discrete_sinusoid_walk dynamixel)

ADD_EXECUTABLE(demo6_reality_exp demo6_reality_exp.cpp actuator.cpp monitor.cpp)
TARGET_LINK_LIBRARIES(demo6_reality_exp dynamixel)

ADD_EXECUTABLE(test1_codamotion test1_codamotion.cpp)
TARGET_LINK_LIBRARIES(test1_codamotion dynamixel)

ADD_EXECUTABLE(test2_codamotion test2_codamotion.cpp)
TARGET_LINK_LIBRARIES(test2_codamotion dynamixel)

