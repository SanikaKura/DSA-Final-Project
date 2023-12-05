cmake_minimum_required(VERSION 3.24)
project(DSA_Final_Project23)

set(CMAKE_CXX_STANDARD 17)

add_executable(DSA_Final_Project23 main.cpp trie.h hashMap.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include/SFML)
target_link_libraries(DSA_Final_Project23 sfml-system sfml-window sfml-graphics sfml-audio)