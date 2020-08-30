# Project
cmake_minimum_required(VERSION 3.1)
project(raytracer)

# Directories
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories(${INCLUDE_DIR})

# Source Files
set(SRC ${SRC_DIR}/main.cpp
        ${SRC_DIR}/sphere.cpp
        ${SRC_DIR}/triangle.cpp
        ${SRC_DIR}/hittable_list.cpp
        ${SRC_DIR}/mesh.cpp)

# Executable Definition
add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}" "${INCLUDE_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)