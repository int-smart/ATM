cmake_minimum_required(VERSION 3.1)

project(atm_main CXX)

enable_language(CXX)

set(CMAKE_CXX_STANDARD 14)
add_executable(atm_main
                src/main.cpp
)
target_include_directories(atm_main
                        PUBLIC include
)