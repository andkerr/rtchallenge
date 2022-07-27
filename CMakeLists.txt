CMAKE_MINIMUM_REQUIRED(VERSION 3.23)
PROJECT(rtchallenge)

set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(
    demos
    src
    src/shapes
)

ADD_LIBRARY(canvas src/canvas.cpp)
ADD_LIBRARY(double src/double.cpp)
ADD_LIBRARY(geometry src/geometry.cpp)
ADD_LIBRARY(matrix src/matrix.cpp)
ADD_LIBRARY(shape src/shape.cpp)
ADD_LIBRARY(sphere src/shapes/sphere.cpp)
ADD_LIBRARY(transform src/transform.cpp)

# Unit Tests

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

FILE(GLOB TEST_SOURCE src/tests/*.cpp)
ADD_EXECUTABLE(rtc_test.exe ${TEST_SOURCE})
TARGET_LINK_LIBRARIES(rtc_test.exe PRIVATE
    Catch2::Catch2WithMain
    canvas
    double
    geometry
    matrix
    shape
    sphere
    transform
)

ADD_EXECUTABLE(projectile.exe demos/projectile.cpp)
TARGET_LINK_LIBRARIES(projectile.exe
    canvas
    double
    geometry
)

ADD_EXECUTABLE(clock.exe demos/clock.cpp)
TARGET_LINK_LIBRARIES(clock.exe
    canvas
    double
    geometry
    matrix
    transform
)