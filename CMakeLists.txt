cmake_minimum_required(VERSION 3.15)
project(PictureBeizer)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(PictureBeizer main.cpp src/Helpers.cpp src/Helpers.h src/PictureReducer.cpp src/PictureReducer.h src/Curve.cpp src/Curve.h)
target_link_libraries(PictureBeizer ${OpenCV_LIBS})