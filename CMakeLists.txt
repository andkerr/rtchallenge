CMAKE_MINIMUM_REQUIRED(VERSION 3.23)
PROJECT(rtchallenge)

set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(
    demos
    src
    src/shapes
)

ADD_LIBRARY(camera src/camera.cpp)
ADD_LIBRARY(canvas src/canvas.cpp)
ADD_LIBRARY(colour src/colour.cpp)
ADD_LIBRARY(double src/double.cpp)
ADD_LIBRARY(geometry src/geometry.cpp)
ADD_LIBRARY(light src/light.cpp)
ADD_LIBRARY(matrix src/matrix.cpp)
ADD_LIBRARY(plane src/shapes/plane.cpp)
ADD_LIBRARY(shape src/shape.cpp)
ADD_LIBRARY(sphere src/shapes/sphere.cpp)
ADD_LIBRARY(transform src/transform.cpp)
ADD_LIBRARY(world src/world.cpp)

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
    camera
    colour
    double
    geometry
    light
    matrix
    plane
    shape
    sphere
    transform
    world
)

ADD_EXECUTABLE(projectile.exe demos/projectile.cpp)
TARGET_LINK_LIBRARIES(projectile.exe
    canvas
    colour
    double
    geometry
)

ADD_EXECUTABLE(clock.exe demos/clock.cpp)
TARGET_LINK_LIBRARIES(clock.exe
    canvas
    colour
    double
    geometry
    matrix
    transform
)

ADD_EXECUTABLE(sphere_silhouette.exe demos/sphere_silhouette.cpp)
TARGET_LINK_LIBRARIES(sphere_silhouette.exe
    canvas
    colour
    double
    geometry
    matrix
    shape
    sphere
    transform
)

ADD_EXECUTABLE(sphere_reflection.exe demos/sphere_reflection.cpp)
TARGET_LINK_LIBRARIES(sphere_reflection.exe
    canvas
    colour
    double
    geometry
    light
    matrix
    shape
    sphere
    transform
)

ADD_EXECUTABLE(world_demo.exe demos/world_demo.cpp)
TARGET_LINK_LIBRARIES(world_demo.exe
    canvas
    camera
    colour
    double
    geometry
    light
    matrix
    shape
    sphere
    transform
    world
)