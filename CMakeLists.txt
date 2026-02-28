cmake_minimum_required(VERSION 3.30)

project(AssetPacker VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_library(AssetPackerTool STATIC
src/AssetPacker.cpp
)
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/AssetPacker.cpp
)

target_include_directories(AssetPackerTool PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE AssetPackerTool)