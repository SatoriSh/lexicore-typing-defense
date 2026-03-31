cmake_minimum_required(VERSION 3.16)

project(LexiCore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(LexiCore src/main.cpp src/dynamic_text/dynamic_text.cpp)

target_include_directories(LexiCore PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(LexiCore PRIVATE SFML::Graphics SFML::Window SFML::System)
