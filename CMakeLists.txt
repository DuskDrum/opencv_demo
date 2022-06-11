cmake_minimum_required(VERSION 3.17)
project(HelloWorld)

set(CMAKE_CXX_STANDARD 14)

#find_library(OpenCV)
find_package(OpenCV)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(HelloWorld opencv_imshow.cpp opencv_imshow.h opencv_cvtcolor_imwrite.cpp opencv_cvtcolor_imwrite.h)

target_link_libraries(HelloWorld ${OpenCV_LIBS})