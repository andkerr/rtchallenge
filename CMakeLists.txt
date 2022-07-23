CMAKE_MINIMUM_REQUIRED(VERSION 3.23)
PROJECT(rtchallenge)

set(CMAKE_CXX_STANDARD 14)

INCLUDE_DIRECTORIES(src)

ADD_LIBRARY(double src/double.cpp)
ADD_LIBRARY(canvas src/canvas.cpp)

# Unit Tests

FIND_PACKAGE(Catch2 3 REQUIRED)

FILE(GLOB TEST_SOURCE src/tests/*.cpp)
ADD_EXECUTABLE(rtc_test.exe ${TEST_SOURCE})
TARGET_LINK_LIBRARIES(rtc_test.exe PRIVATE
    Catch2::Catch2WithMain
    double
    canvas
)