cmake_minimum_required(VERSION 4.0)
project(Adv_Game_Prog_Tech)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    set(SDL3_PATH "C:/Dev/SDL3")
    include_directories(${SDL3_PATH}/include)
    link_directories(${SDL3_PATH}/lib)
endif ()

add_executable(Adv_Game_Prog_Tech main.cpp
        Game.cpp)

target_link_libraries(Adv_Game_Prog_Tech
        SDL3
)
