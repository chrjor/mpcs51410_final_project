cmake_minimum_required(VERSION 3.5)

project(
    MPCS5410_Project
    VERSION 1.0
    LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.3.0
)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

include(CTest)
include(Catch)

add_subdirectory(Project)
add_subdirectory(ProjectTests)
