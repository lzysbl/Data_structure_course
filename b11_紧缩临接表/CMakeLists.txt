cmake_minimum_required(VERSION 3.10)

project(class)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES_DIR "src/*.cpp")

include_directories(${PROJECT_SOURCE_DIR}/include/)

add_executable(class main.cpp ${SOURCES_DIR})

find_package(OpenCV REQUIRED)

target_link_libraries(class
        ${OpenCV_LIBS}
)
