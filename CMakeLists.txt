cmake_minimum_required(VERSION 3.16)

project(LexiCore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address -fsanitize=undefined") # для дебага

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(LexiCore src/main.cpp src/game/game_manager.cpp src/heart/heart.cpp src/dynamic_text/dynamic_text.cpp src/circle/circle.cpp)

target_include_directories(LexiCore PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(LexiCore PRIVATE SFML::Graphics SFML::Window SFML::System)
