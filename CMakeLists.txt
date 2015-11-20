CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(LightDBMS)

FILE(GLOB dbms_sources "${PROJECT_SOURCE_DIR}/*.cpp")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic-errors")

ADD_EXECUTABLE(dbms ${dbms_sources})

