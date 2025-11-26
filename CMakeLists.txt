cmake_minimum_required(VERSION 3.10)
project(MiniDesign)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(MiniDesign ${SOURCES})
set_target_properties(MiniDesign PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

add_executable(tests tests.cpp ${SOURCES})
set_target_properties(tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)
