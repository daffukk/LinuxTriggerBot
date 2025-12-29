cmake_minimum_required(VERSION 3.10)
project(LinuxTriggerBot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_executable(LinuxTriggerBot main.cpp imgCompare.cpp)
target_link_libraries(LinuxTriggerBot ${OpenCV_LIBS})
